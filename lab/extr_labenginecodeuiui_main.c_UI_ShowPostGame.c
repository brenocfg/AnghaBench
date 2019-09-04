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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/  soundHighScore; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIMENU_POSTGAME ; 
 int /*<<< orphan*/  _UI_SetActiveMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 TYPE_1__ uiInfo ; 

void UI_ShowPostGame(qboolean newHigh) {
	trap_Cvar_Set ("cg_cameraOrbit", "0");
	trap_Cvar_Set("cg_thirdPerson", "0");
	uiInfo.soundHighScore = newHigh;
  _UI_SetActiveMenu(UIMENU_POSTGAME);
}