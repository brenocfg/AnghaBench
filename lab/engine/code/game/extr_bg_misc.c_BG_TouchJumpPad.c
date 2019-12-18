#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_6__ {scalar_t__ pm_type; scalar_t__ jumppad_ent; int /*<<< orphan*/  velocity; int /*<<< orphan*/  pmove_framecount; int /*<<< orphan*/  jumppad_frame; scalar_t__* powerups; } ;
typedef  TYPE_1__ playerState_t ;
struct TYPE_7__ {scalar_t__ number; int /*<<< orphan*/  origin2; } ;
typedef  TYPE_2__ entityState_t ;

/* Variables and functions */
 int /*<<< orphan*/  AngleNormalize180 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BG_AddPredictableEventToPlayerstate (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  EV_JUMP_PAD ; 
 size_t PITCH ; 
 scalar_t__ PM_NORMAL ; 
 size_t PW_FLIGHT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void BG_TouchJumpPad( playerState_t *ps, entityState_t *jumppad ) {
	vec3_t	angles;
	float p;
	int effectNum;

	// spectators don't use jump pads
	if ( ps->pm_type != PM_NORMAL ) {
		return;
	}

	// flying characters don't hit bounce pads
	if ( ps->powerups[PW_FLIGHT] ) {
		return;
	}

	// if we didn't hit this same jumppad the previous frame
	// then don't play the event sound again if we are in a fat trigger
	if ( ps->jumppad_ent != jumppad->number ) {

		vectoangles( jumppad->origin2, angles);
		p = fabs( AngleNormalize180( angles[PITCH] ) );
		if( p < 45 ) {
			effectNum = 0;
		} else {
			effectNum = 1;
		}
		BG_AddPredictableEventToPlayerstate( EV_JUMP_PAD, effectNum, ps );
	}
	// remember hitting this jumppad this frame
	ps->jumppad_ent = jumppad->number;
	ps->jumppad_frame = ps->pmove_framecount;
	// give the player the velocity from the jumppad
	VectorCopy( jumppad->origin2, ps->velocity );
}