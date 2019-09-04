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
struct TYPE_2__ {size_t selectedmodel; int /*<<< orphan*/ * pics; int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 size_t MAX_MODELSPERPAGE ; 
 int /*<<< orphan*/  Menu_SetCursorToItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PlayerModel_MenuInit () ; 
 int /*<<< orphan*/  UI_PushMenu (int /*<<< orphan*/ *) ; 
 TYPE_1__ s_playermodel ; 

void UI_PlayerModelMenu(void)
{
	PlayerModel_MenuInit();

	UI_PushMenu( &s_playermodel.menu );

	Menu_SetCursorToItem( &s_playermodel.menu, &s_playermodel.pics[s_playermodel.selectedmodel % MAX_MODELSPERPAGE] );
}