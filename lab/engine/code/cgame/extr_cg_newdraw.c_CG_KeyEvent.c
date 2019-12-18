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
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {scalar_t__ pm_type; } ;
struct TYPE_6__ {scalar_t__ showScores; TYPE_1__ predictedPlayerState; } ;
struct TYPE_5__ {int /*<<< orphan*/  cursorY; int /*<<< orphan*/  cursorX; int /*<<< orphan*/ * capturedItem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGAME_EVENT_NONE ; 
 int /*<<< orphan*/  CG_EventHandling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Display_CaptureItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Display_HandleKey (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int K_MOUSE2 ; 
 scalar_t__ PM_NORMAL ; 
 scalar_t__ PM_SPECTATOR ; 
 TYPE_3__ cg ; 
 TYPE_2__ cgs ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  trap_Key_SetCatcher (int /*<<< orphan*/ ) ; 

void CG_KeyEvent(int key, qboolean down) {

	if (!down) {
		return;
	}

	if ( cg.predictedPlayerState.pm_type == PM_NORMAL || (cg.predictedPlayerState.pm_type == PM_SPECTATOR && cg.showScores == qfalse)) {
		CG_EventHandling(CGAME_EVENT_NONE);
    trap_Key_SetCatcher(0);
		return;
	}

  //if (key == trap_Key_GetKey("teamMenu") || !Display_CaptureItem(cgs.cursorX, cgs.cursorY)) {
    // if we see this then we should always be visible
  //  CG_EventHandling(CGAME_EVENT_NONE);
  //  trap_Key_SetCatcher(0);
  //}



  Display_HandleKey(key, down, cgs.cursorX, cgs.cursorY);

	if (cgs.capturedItem) {
		cgs.capturedItem = NULL;
	}	else {
		if (key == K_MOUSE2 && down) {
			cgs.capturedItem = Display_CaptureItem(cgs.cursorX, cgs.cursorY);
		}
	}
}