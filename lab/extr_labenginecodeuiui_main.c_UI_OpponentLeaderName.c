#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* teamList; } ;
struct TYPE_3__ {char const** teamMembers; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_Cvar_VariableString (char*) ; 
 int UI_TeamIndexFromName (int /*<<< orphan*/ ) ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static const char *UI_OpponentLeaderName(void) {
  int i = UI_TeamIndexFromName(UI_Cvar_VariableString("ui_opponentName"));
	return uiInfo.teamList[i].teamMembers[0];
}