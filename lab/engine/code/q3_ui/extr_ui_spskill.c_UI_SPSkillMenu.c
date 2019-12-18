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
struct TYPE_2__ {char const* arenaInfo; int /*<<< orphan*/  item_fight; int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_SetCursorToItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_PushMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_SPSkillMenu_Init () ; 
 TYPE_1__ skillMenuInfo ; 

void UI_SPSkillMenu( const char *arenaInfo ) {
	UI_SPSkillMenu_Init();
	skillMenuInfo.arenaInfo = arenaInfo;
	UI_PushMenu( &skillMenuInfo.menu );
	Menu_SetCursorToItem( &skillMenuInfo.menu, &skillMenuInfo.item_fight );
}