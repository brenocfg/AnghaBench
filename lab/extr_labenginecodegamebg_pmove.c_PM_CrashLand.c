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
struct TYPE_8__ {int waterlevel; TYPE_2__* ps; } ;
struct TYPE_5__ {int surfaceFlags; } ;
struct TYPE_7__ {float* previous_origin; float* previous_velocity; TYPE_1__ groundTrace; } ;
struct TYPE_6__ {int pm_flags; float* origin; float gravity; scalar_t__* stats; scalar_t__ bobCycle; int /*<<< orphan*/  legsTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_FALL_FAR ; 
 int /*<<< orphan*/  EV_FALL_MEDIUM ; 
 int /*<<< orphan*/  EV_FALL_SHORT ; 
 int /*<<< orphan*/  LEGS_LAND ; 
 int /*<<< orphan*/  LEGS_LANDB ; 
 int PMF_BACKWARDS_JUMP ; 
 int PMF_DUCKED ; 
 int /*<<< orphan*/  PM_AddEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_FootstepForSurface () ; 
 int /*<<< orphan*/  PM_ForceLegsAnim (int /*<<< orphan*/ ) ; 
 size_t STAT_HEALTH ; 
 int SURF_NODAMAGE ; 
 int /*<<< orphan*/  TIMER_LAND ; 
 TYPE_4__* pm ; 
 TYPE_3__ pml ; 
 float sqrt (float) ; 

__attribute__((used)) static void PM_CrashLand( void ) {
	float		delta;
	float		dist;
	float		vel, acc;
	float		t;
	float		a, b, c, den;

	// decide which landing animation to use
	if ( pm->ps->pm_flags & PMF_BACKWARDS_JUMP ) {
		PM_ForceLegsAnim( LEGS_LANDB );
	} else {
		PM_ForceLegsAnim( LEGS_LAND );
	}

	pm->ps->legsTimer = TIMER_LAND;

	// calculate the exact velocity on landing
	dist = pm->ps->origin[2] - pml.previous_origin[2];
	vel = pml.previous_velocity[2];
	acc = -pm->ps->gravity;

	a = acc / 2;
	b = vel;
	c = -dist;

	den =  b * b - 4 * a * c;
	if ( den < 0 ) {
		return;
	}
	t = (-b - sqrt( den ) ) / ( 2 * a );

	delta = vel + t * acc;
	delta = delta*delta * 0.0001;

	// ducking while falling doubles damage
	if ( pm->ps->pm_flags & PMF_DUCKED ) {
		delta *= 2;
	}

	// never take falling damage if completely underwater
	if ( pm->waterlevel == 3 ) {
		return;
	}

	// reduce falling damage if there is standing water
	if ( pm->waterlevel == 2 ) {
		delta *= 0.25;
	}
	if ( pm->waterlevel == 1 ) {
		delta *= 0.5;
	}

	if ( delta < 1 ) {
		return;
	}

	// create a local entity event to play the sound

	// SURF_NODAMAGE is used for bounce pads where you don't ever
	// want to take damage or play a crunch sound
	if ( !(pml.groundTrace.surfaceFlags & SURF_NODAMAGE) )  {
		if ( delta > 60 ) {
			PM_AddEvent( EV_FALL_FAR );
		} else if ( delta > 40 ) {
			// this is a pain grunt, so don't play it if dead
			if ( pm->ps->stats[STAT_HEALTH] > 0 ) {
				PM_AddEvent( EV_FALL_MEDIUM );
			}
		} else if ( delta > 7 ) {
			PM_AddEvent( EV_FALL_SHORT );
		} else {
			PM_AddEvent( PM_FootstepForSurface() );
		}
	}

	// start footstep cycle over
	pm->ps->bobCycle = 0;
}