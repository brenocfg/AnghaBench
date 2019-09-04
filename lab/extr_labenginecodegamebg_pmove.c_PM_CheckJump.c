#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_5__ {int upmove; scalar_t__ forwardmove; } ;
struct TYPE_8__ {TYPE_2__* ps; TYPE_1__ cmd; } ;
struct TYPE_7__ {void* walking; void* groundPlane; } ;
struct TYPE_6__ {int pm_flags; int /*<<< orphan*/ * velocity; int /*<<< orphan*/  groundEntityNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTITYNUM_NONE ; 
 int /*<<< orphan*/  EV_JUMP ; 
 int /*<<< orphan*/  JUMP_VELOCITY ; 
 int /*<<< orphan*/  LEGS_JUMP ; 
 int /*<<< orphan*/  LEGS_JUMPB ; 
 int PMF_BACKWARDS_JUMP ; 
 int PMF_JUMP_HELD ; 
 int PMF_RESPAWNED ; 
 int /*<<< orphan*/  PM_AddEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_ForceLegsAnim (int /*<<< orphan*/ ) ; 
 TYPE_4__* pm ; 
 TYPE_3__ pml ; 
 void* qfalse ; 
 void* qtrue ; 

__attribute__((used)) static qboolean PM_CheckJump( void ) {
	if ( pm->ps->pm_flags & PMF_RESPAWNED ) {
		return qfalse;		// don't allow jump until all buttons are up
	}

	if ( pm->cmd.upmove < 10 ) {
		// not holding jump
		return qfalse;
	}

	// must wait for jump to be released
	if ( pm->ps->pm_flags & PMF_JUMP_HELD ) {
		// clear upmove so cmdscale doesn't lower running speed
		pm->cmd.upmove = 0;
		return qfalse;
	}

	pml.groundPlane = qfalse;		// jumping away
	pml.walking = qfalse;
	pm->ps->pm_flags |= PMF_JUMP_HELD;

	pm->ps->groundEntityNum = ENTITYNUM_NONE;
	pm->ps->velocity[2] = JUMP_VELOCITY;
	PM_AddEvent( EV_JUMP );

	if ( pm->cmd.forwardmove >= 0 ) {
		PM_ForceLegsAnim( LEGS_JUMP );
		pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
	} else {
		PM_ForceLegsAnim( LEGS_JUMPB );
		pm->ps->pm_flags |= PMF_BACKWARDS_JUMP;
	}

	return qtrue;
}