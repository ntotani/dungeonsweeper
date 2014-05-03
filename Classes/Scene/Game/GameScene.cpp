#include "GameScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "cocosbuilder/CCNodeLoaderLibrary.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("GameScene", GameSceneLoader::loader());
    auto ccbReader = new CCBReader(nodeLoaderLibrary);
    ccbReader->autorelease();
    auto layer = ccbReader->readNodeGraphFromFile("ccbi/GameScene.ccbi");
    //static_cast<PuzzleScene*>(layer)->initStoneLayer();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    row = 10;
    col = 10;
    auto layer = Layer::create();
    for (int i = 0; i< row; i++) {
        vector<Tile> line;
        for (int j = 0; j < col; j++) {
            line.push_back(Tile::HIDE);
            auto sp = Sprite::create("img/block.png");
            auto len = sp->getContentSize().width;
            sp->setPosition(Point(j + 0.5f, row - 1 - i + 0.5f) * len);
            layer->addChild(sp);
        }
        tiles.push_back(line);
    }
    addChild(layer);

    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadEffect("sound/se_coin.mp3");
    audio->preloadEffect("sound/se_ob.mp3");

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {return true;};
    listener->onTouchMoved = [](Touch* touch, Event* event) {};
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = [](Touch* touch, Event* event) {};
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    scheduleUpdate();
    return true;
}

bool GameScene::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "manaA", Node*, manaA);
    return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
}

void GameScene::update(float dt)
{
}
