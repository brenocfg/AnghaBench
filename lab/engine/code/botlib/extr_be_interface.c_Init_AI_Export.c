#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  GeneticParentsAndChildSelection; int /*<<< orphan*/  BotResetWeaponState; int /*<<< orphan*/  BotFreeWeaponState; int /*<<< orphan*/  BotAllocWeaponState; int /*<<< orphan*/  BotLoadWeaponWeights; int /*<<< orphan*/  BotGetWeaponInfo; int /*<<< orphan*/  BotChooseBestFightWeapon; int /*<<< orphan*/  BotAddAvoidSpot; int /*<<< orphan*/  BotInitMoveState; int /*<<< orphan*/  BotFreeMoveState; int /*<<< orphan*/  BotAllocMoveState; int /*<<< orphan*/  BotPredictVisiblePosition; int /*<<< orphan*/  BotMovementViewTarget; int /*<<< orphan*/  BotReachabilityArea; int /*<<< orphan*/  BotResetLastAvoidReach; int /*<<< orphan*/  BotResetAvoidReach; int /*<<< orphan*/  BotMoveInDirection; int /*<<< orphan*/  BotMoveToGoal; int /*<<< orphan*/  BotResetMoveState; int /*<<< orphan*/  BotFreeGoalState; int /*<<< orphan*/  BotAllocGoalState; int /*<<< orphan*/  BotMutateGoalFuzzyLogic; int /*<<< orphan*/  BotSaveGoalFuzzyLogic; int /*<<< orphan*/  BotInterbreedGoalFuzzyLogic; int /*<<< orphan*/  BotFreeItemWeights; int /*<<< orphan*/  BotLoadItemWeights; int /*<<< orphan*/  BotUpdateEntityItems; int /*<<< orphan*/  BotInitLevelItems; int /*<<< orphan*/  BotSetAvoidGoalTime; int /*<<< orphan*/  BotAvoidGoalTime; int /*<<< orphan*/  BotGetMapLocationGoal; int /*<<< orphan*/  BotGetNextCampSpotGoal; int /*<<< orphan*/  BotGetLevelItemGoal; int /*<<< orphan*/  BotItemGoalInVisButNotVisible; int /*<<< orphan*/  BotTouchingGoal; int /*<<< orphan*/  BotChooseNBGItem; int /*<<< orphan*/  BotChooseLTGItem; int /*<<< orphan*/  BotGetSecondGoal; int /*<<< orphan*/  BotGetTopGoal; int /*<<< orphan*/  BotGoalName; int /*<<< orphan*/  BotDumpGoalStack; int /*<<< orphan*/  BotDumpAvoidGoals; int /*<<< orphan*/  BotEmptyGoalStack; int /*<<< orphan*/  BotPopGoal; int /*<<< orphan*/  BotPushGoal; int /*<<< orphan*/  BotRemoveFromAvoidGoals; int /*<<< orphan*/  BotResetAvoidGoals; int /*<<< orphan*/  BotResetGoalState; int /*<<< orphan*/  BotSetChatName; int /*<<< orphan*/  BotSetChatGender; int /*<<< orphan*/  BotLoadChatFile; int /*<<< orphan*/  BotReplaceSynonyms; int /*<<< orphan*/  UnifyWhiteSpaces; int /*<<< orphan*/  BotMatchVariable; int /*<<< orphan*/  BotFindMatch; int /*<<< orphan*/  StringContains; int /*<<< orphan*/  BotGetChatMessage; int /*<<< orphan*/  BotEnterChat; int /*<<< orphan*/  BotChatLength; int /*<<< orphan*/  BotReplyChat; int /*<<< orphan*/  BotNumInitialChats; int /*<<< orphan*/  BotInitialChat; int /*<<< orphan*/  BotNumConsoleMessages; int /*<<< orphan*/  BotNextConsoleMessage; int /*<<< orphan*/  BotRemoveConsoleMessage; int /*<<< orphan*/  BotQueueConsoleMessage; int /*<<< orphan*/  BotFreeChatState; int /*<<< orphan*/  BotAllocChatState; int /*<<< orphan*/  Characteristic_String; int /*<<< orphan*/  Characteristic_BInteger; int /*<<< orphan*/  Characteristic_Integer; int /*<<< orphan*/  Characteristic_BFloat; int /*<<< orphan*/  Characteristic_Float; int /*<<< orphan*/  BotFreeCharacter; int /*<<< orphan*/  BotLoadCharacter; } ;
typedef  TYPE_1__ ai_export_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAddAvoidSpot ; 
 int /*<<< orphan*/  BotAllocChatState ; 
 int /*<<< orphan*/  BotAllocGoalState ; 
 int /*<<< orphan*/  BotAllocMoveState ; 
 int /*<<< orphan*/  BotAllocWeaponState ; 
 int /*<<< orphan*/  BotAvoidGoalTime ; 
 int /*<<< orphan*/  BotChatLength ; 
 int /*<<< orphan*/  BotChooseBestFightWeapon ; 
 int /*<<< orphan*/  BotChooseLTGItem ; 
 int /*<<< orphan*/  BotChooseNBGItem ; 
 int /*<<< orphan*/  BotDumpAvoidGoals ; 
 int /*<<< orphan*/  BotDumpGoalStack ; 
 int /*<<< orphan*/  BotEmptyGoalStack ; 
 int /*<<< orphan*/  BotEnterChat ; 
 int /*<<< orphan*/  BotFindMatch ; 
 int /*<<< orphan*/  BotFreeCharacter ; 
 int /*<<< orphan*/  BotFreeChatState ; 
 int /*<<< orphan*/  BotFreeGoalState ; 
 int /*<<< orphan*/  BotFreeItemWeights ; 
 int /*<<< orphan*/  BotFreeMoveState ; 
 int /*<<< orphan*/  BotFreeWeaponState ; 
 int /*<<< orphan*/  BotGetChatMessage ; 
 int /*<<< orphan*/  BotGetLevelItemGoal ; 
 int /*<<< orphan*/  BotGetMapLocationGoal ; 
 int /*<<< orphan*/  BotGetNextCampSpotGoal ; 
 int /*<<< orphan*/  BotGetSecondGoal ; 
 int /*<<< orphan*/  BotGetTopGoal ; 
 int /*<<< orphan*/  BotGetWeaponInfo ; 
 int /*<<< orphan*/  BotGoalName ; 
 int /*<<< orphan*/  BotInitLevelItems ; 
 int /*<<< orphan*/  BotInitMoveState ; 
 int /*<<< orphan*/  BotInitialChat ; 
 int /*<<< orphan*/  BotInterbreedGoalFuzzyLogic ; 
 int /*<<< orphan*/  BotItemGoalInVisButNotVisible ; 
 int /*<<< orphan*/  BotLoadCharacter ; 
 int /*<<< orphan*/  BotLoadChatFile ; 
 int /*<<< orphan*/  BotLoadItemWeights ; 
 int /*<<< orphan*/  BotLoadWeaponWeights ; 
 int /*<<< orphan*/  BotMatchVariable ; 
 int /*<<< orphan*/  BotMoveInDirection ; 
 int /*<<< orphan*/  BotMoveToGoal ; 
 int /*<<< orphan*/  BotMovementViewTarget ; 
 int /*<<< orphan*/  BotMutateGoalFuzzyLogic ; 
 int /*<<< orphan*/  BotNextConsoleMessage ; 
 int /*<<< orphan*/  BotNumConsoleMessages ; 
 int /*<<< orphan*/  BotNumInitialChats ; 
 int /*<<< orphan*/  BotPopGoal ; 
 int /*<<< orphan*/  BotPredictVisiblePosition ; 
 int /*<<< orphan*/  BotPushGoal ; 
 int /*<<< orphan*/  BotQueueConsoleMessage ; 
 int /*<<< orphan*/  BotReachabilityArea ; 
 int /*<<< orphan*/  BotRemoveConsoleMessage ; 
 int /*<<< orphan*/  BotRemoveFromAvoidGoals ; 
 int /*<<< orphan*/  BotReplaceSynonyms ; 
 int /*<<< orphan*/  BotReplyChat ; 
 int /*<<< orphan*/  BotResetAvoidGoals ; 
 int /*<<< orphan*/  BotResetAvoidReach ; 
 int /*<<< orphan*/  BotResetGoalState ; 
 int /*<<< orphan*/  BotResetLastAvoidReach ; 
 int /*<<< orphan*/  BotResetMoveState ; 
 int /*<<< orphan*/  BotResetWeaponState ; 
 int /*<<< orphan*/  BotSaveGoalFuzzyLogic ; 
 int /*<<< orphan*/  BotSetAvoidGoalTime ; 
 int /*<<< orphan*/  BotSetChatGender ; 
 int /*<<< orphan*/  BotSetChatName ; 
 int /*<<< orphan*/  BotTouchingGoal ; 
 int /*<<< orphan*/  BotUpdateEntityItems ; 
 int /*<<< orphan*/  Characteristic_BFloat ; 
 int /*<<< orphan*/  Characteristic_BInteger ; 
 int /*<<< orphan*/  Characteristic_Float ; 
 int /*<<< orphan*/  Characteristic_Integer ; 
 int /*<<< orphan*/  Characteristic_String ; 
 int /*<<< orphan*/  GeneticParentsAndChildSelection ; 
 int /*<<< orphan*/  StringContains ; 
 int /*<<< orphan*/  UnifyWhiteSpaces ; 

__attribute__((used)) static void Init_AI_Export( ai_export_t *ai ) {
	//-----------------------------------
	// be_ai_char.h
	//-----------------------------------
	ai->BotLoadCharacter = BotLoadCharacter;
	ai->BotFreeCharacter = BotFreeCharacter;
	ai->Characteristic_Float = Characteristic_Float;
	ai->Characteristic_BFloat = Characteristic_BFloat;
	ai->Characteristic_Integer = Characteristic_Integer;
	ai->Characteristic_BInteger = Characteristic_BInteger;
	ai->Characteristic_String = Characteristic_String;
	//-----------------------------------
	// be_ai_chat.h
	//-----------------------------------
	ai->BotAllocChatState = BotAllocChatState;
	ai->BotFreeChatState = BotFreeChatState;
	ai->BotQueueConsoleMessage = BotQueueConsoleMessage;
	ai->BotRemoveConsoleMessage = BotRemoveConsoleMessage;
	ai->BotNextConsoleMessage = BotNextConsoleMessage;
	ai->BotNumConsoleMessages = BotNumConsoleMessages;
	ai->BotInitialChat = BotInitialChat;
	ai->BotNumInitialChats = BotNumInitialChats;
	ai->BotReplyChat = BotReplyChat;
	ai->BotChatLength = BotChatLength;
	ai->BotEnterChat = BotEnterChat;
	ai->BotGetChatMessage = BotGetChatMessage;
	ai->StringContains = StringContains;
	ai->BotFindMatch = BotFindMatch;
	ai->BotMatchVariable = BotMatchVariable;
	ai->UnifyWhiteSpaces = UnifyWhiteSpaces;
	ai->BotReplaceSynonyms = BotReplaceSynonyms;
	ai->BotLoadChatFile = BotLoadChatFile;
	ai->BotSetChatGender = BotSetChatGender;
	ai->BotSetChatName = BotSetChatName;
	//-----------------------------------
	// be_ai_goal.h
	//-----------------------------------
	ai->BotResetGoalState = BotResetGoalState;
	ai->BotResetAvoidGoals = BotResetAvoidGoals;
	ai->BotRemoveFromAvoidGoals = BotRemoveFromAvoidGoals;
	ai->BotPushGoal = BotPushGoal;
	ai->BotPopGoal = BotPopGoal;
	ai->BotEmptyGoalStack = BotEmptyGoalStack;
	ai->BotDumpAvoidGoals = BotDumpAvoidGoals;
	ai->BotDumpGoalStack = BotDumpGoalStack;
	ai->BotGoalName = BotGoalName;
	ai->BotGetTopGoal = BotGetTopGoal;
	ai->BotGetSecondGoal = BotGetSecondGoal;
	ai->BotChooseLTGItem = BotChooseLTGItem;
	ai->BotChooseNBGItem = BotChooseNBGItem;
	ai->BotTouchingGoal = BotTouchingGoal;
	ai->BotItemGoalInVisButNotVisible = BotItemGoalInVisButNotVisible;
	ai->BotGetLevelItemGoal = BotGetLevelItemGoal;
	ai->BotGetNextCampSpotGoal = BotGetNextCampSpotGoal;
	ai->BotGetMapLocationGoal = BotGetMapLocationGoal;
	ai->BotAvoidGoalTime = BotAvoidGoalTime;
	ai->BotSetAvoidGoalTime = BotSetAvoidGoalTime;
	ai->BotInitLevelItems = BotInitLevelItems;
	ai->BotUpdateEntityItems = BotUpdateEntityItems;
	ai->BotLoadItemWeights = BotLoadItemWeights;
	ai->BotFreeItemWeights = BotFreeItemWeights;
	ai->BotInterbreedGoalFuzzyLogic = BotInterbreedGoalFuzzyLogic;
	ai->BotSaveGoalFuzzyLogic = BotSaveGoalFuzzyLogic;
	ai->BotMutateGoalFuzzyLogic = BotMutateGoalFuzzyLogic;
	ai->BotAllocGoalState = BotAllocGoalState;
	ai->BotFreeGoalState = BotFreeGoalState;
	//-----------------------------------
	// be_ai_move.h
	//-----------------------------------
	ai->BotResetMoveState = BotResetMoveState;
	ai->BotMoveToGoal = BotMoveToGoal;
	ai->BotMoveInDirection = BotMoveInDirection;
	ai->BotResetAvoidReach = BotResetAvoidReach;
	ai->BotResetLastAvoidReach = BotResetLastAvoidReach;
	ai->BotReachabilityArea = BotReachabilityArea;
	ai->BotMovementViewTarget = BotMovementViewTarget;
	ai->BotPredictVisiblePosition = BotPredictVisiblePosition;
	ai->BotAllocMoveState = BotAllocMoveState;
	ai->BotFreeMoveState = BotFreeMoveState;
	ai->BotInitMoveState = BotInitMoveState;
	ai->BotAddAvoidSpot = BotAddAvoidSpot;
	//-----------------------------------
	// be_ai_weap.h
	//-----------------------------------
	ai->BotChooseBestFightWeapon = BotChooseBestFightWeapon;
	ai->BotGetWeaponInfo = BotGetWeaponInfo;
	ai->BotLoadWeaponWeights = BotLoadWeaponWeights;
	ai->BotAllocWeaponState = BotAllocWeaponState;
	ai->BotFreeWeaponState = BotFreeWeaponState;
	ai->BotResetWeaponState = BotResetWeaponState;
	//-----------------------------------
	// be_ai_gen.h
	//-----------------------------------
	ai->GeneticParentsAndChildSelection = GeneticParentsAndChildSelection;
}