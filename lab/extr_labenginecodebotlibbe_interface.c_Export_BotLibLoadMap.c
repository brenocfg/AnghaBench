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
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int AAS_LoadMap (char const*) ; 
 int BLERR_LIBRARYNOTSETUP ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  BotInitLevelItems () ; 
 int /*<<< orphan*/  BotLibSetup (char*) ; 
 int /*<<< orphan*/  BotSetBrushModelTypes () ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 

int Export_BotLibLoadMap(const char *mapname)
{
#ifdef DEBUG
	int starttime = Sys_MilliSeconds();
#endif
	int errnum;

	if (!BotLibSetup("BotLoadMap")) return BLERR_LIBRARYNOTSETUP;
	//
	botimport.Print(PRT_MESSAGE, "------------ Map Loading ------------\n");
	//startup AAS for the current map, model and sound index
	errnum = AAS_LoadMap(mapname);
	if (errnum != BLERR_NOERROR) return errnum;
	//initialize the items in the level
	BotInitLevelItems();		//be_ai_goal.h
	BotSetBrushModelTypes();	//be_ai_move.h
	//
	botimport.Print(PRT_MESSAGE, "-------------------------------------\n");
#ifdef DEBUG
	botimport.Print(PRT_MESSAGE, "map loaded in %d msec\n", Sys_MilliSeconds() - starttime);
#endif
	//
	return BLERR_NOERROR;
}