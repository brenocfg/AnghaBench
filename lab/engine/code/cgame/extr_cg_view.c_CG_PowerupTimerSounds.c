#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int time; int oldTime; TYPE_3__* snap; } ;
struct TYPE_6__ {int /*<<< orphan*/  wearOffSound; } ;
struct TYPE_9__ {TYPE_1__ media; } ;
struct TYPE_7__ {int* powerups; int /*<<< orphan*/  clientNum; } ;
struct TYPE_8__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ITEM ; 
 int MAX_POWERUPS ; 
 int POWERUP_BLINKS ; 
 int POWERUP_BLINK_TIME ; 
 TYPE_5__ cg ; 
 TYPE_4__ cgs ; 
 int /*<<< orphan*/  trap_S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_PowerupTimerSounds( void ) {
	int		i;
	int		t;

	// powerup timers going away
	for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
		t = cg.snap->ps.powerups[i];
		if ( t <= cg.time ) {
			continue;
		}
		if ( t - cg.time >= POWERUP_BLINKS * POWERUP_BLINK_TIME ) {
			continue;
		}
		if ( ( t - cg.time ) / POWERUP_BLINK_TIME != ( t - cg.oldTime ) / POWERUP_BLINK_TIME ) {
			trap_S_StartSound( NULL, cg.snap->ps.clientNum, CHAN_ITEM, cgs.media.wearOffSound );
		}
	}
}