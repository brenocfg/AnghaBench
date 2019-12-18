#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* botlibsetup; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Shutdown () ; 
 int BLERR_LIBRARYNOTSETUP ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  BotLibSetup (char*) ; 
 int /*<<< orphan*/  BotShutdownCharacters () ; 
 int /*<<< orphan*/  BotShutdownChatAI () ; 
 int /*<<< orphan*/  BotShutdownGoalAI () ; 
 int /*<<< orphan*/  BotShutdownMoveAI () ; 
 int /*<<< orphan*/  BotShutdownWeaponAI () ; 
 int /*<<< orphan*/  BotShutdownWeights () ; 
 int /*<<< orphan*/  EA_Shutdown () ; 
 int /*<<< orphan*/  LibVarDeAllocAll () ; 
 int /*<<< orphan*/  Log_Shutdown () ; 
 int /*<<< orphan*/  PC_CheckOpenSourceHandles () ; 
 int /*<<< orphan*/  PC_RemoveAllGlobalDefines () ; 
 int /*<<< orphan*/  PrintMemoryLabels () ; 
 TYPE_1__ botlibglobals ; 
 void* botlibsetup ; 
 void* qfalse ; 

int Export_BotLibShutdown(void)
{
	if (!BotLibSetup("BotLibShutdown")) return BLERR_LIBRARYNOTSETUP;
#ifndef DEMO
	//DumpFileCRCs();
#endif //DEMO
	//
	BotShutdownChatAI();		//be_ai_chat.c
	BotShutdownMoveAI();		//be_ai_move.c
	BotShutdownGoalAI();		//be_ai_goal.c
	BotShutdownWeaponAI();		//be_ai_weap.c
	BotShutdownWeights();		//be_ai_weight.c
	BotShutdownCharacters();	//be_ai_char.c
	//shud down aas
	AAS_Shutdown();
	//shut down bot elemantary actions
	EA_Shutdown();
	//free all libvars
	LibVarDeAllocAll();
	//remove all global defines from the pre compiler
	PC_RemoveAllGlobalDefines();

	//dump all allocated memory
//	DumpMemory();
#ifdef DEBUG
	PrintMemoryLabels();
#endif
	//shut down library log file
	Log_Shutdown();
	//
	botlibsetup = qfalse;
	botlibglobals.botlibsetup = qfalse;
	// print any files still open
	PC_CheckOpenSourceHandles();
	//
	return BLERR_NOERROR;
}