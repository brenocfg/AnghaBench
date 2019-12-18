#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int curvalue; } ;
struct TYPE_4__ {char** itemnames; size_t curvalue; } ;
struct TYPE_6__ {size_t selectedBotNum; int delay; int /*<<< orphan*/ * botnames; TYPE_2__ skill; TYPE_1__ team; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
 int QM_ACTIVATED ; 
 TYPE_3__ addBotsMenuInfo ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ,int,char const*,int) ; 

__attribute__((used)) static void UI_AddBotsMenu_FightEvent( void* ptr, int event ) {
	const char	*team;
	int			skill;

	if (event != QM_ACTIVATED) {
		return;
	}

	team = addBotsMenuInfo.team.itemnames[addBotsMenuInfo.team.curvalue];
	skill = addBotsMenuInfo.skill.curvalue + 1;

	trap_Cmd_ExecuteText( EXEC_APPEND, va("addbot %s %i %s %i\n",
		addBotsMenuInfo.botnames[addBotsMenuInfo.selectedBotNum], skill, team, addBotsMenuInfo.delay) );

	addBotsMenuInfo.delay += 1500;
}