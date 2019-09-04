#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rectDef_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_7__ {int /*<<< orphan*/  teamTask; } ;
typedef  TYPE_2__ clientInfo_t ;
struct TYPE_9__ {int time; } ;
struct TYPE_8__ {int orderTime; int /*<<< orphan*/  currentOrder; scalar_t__ orderPending; TYPE_2__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DrawPic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t CG_GetSelectedPlayer () ; 
 int /*<<< orphan*/  CG_StatusHandle (int /*<<< orphan*/ ) ; 
 TYPE_4__ cg ; 
 TYPE_3__ cgs ; 
 int* sortedTeamPlayers ; 

__attribute__((used)) static void CG_DrawSelectedPlayerStatus( rectDef_t *rect ) {
	clientInfo_t *ci = cgs.clientinfo + sortedTeamPlayers[CG_GetSelectedPlayer()];
	if (ci) {
		qhandle_t h;
		if (cgs.orderPending) {
			// blink the icon
			if ( cg.time > cgs.orderTime - 2500 && (cg.time >> 9 ) & 1 ) {
				return;
			}
			h = CG_StatusHandle(cgs.currentOrder);
		}	else {
			h = CG_StatusHandle(ci->teamTask);
		}
		CG_DrawPic( rect->x, rect->y, rect->w, rect->h, h );
	}
}