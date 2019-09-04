#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_11__ {float forwardmove; float rightmove; } ;
typedef  TYPE_4__ usercmd_t ;
struct TYPE_13__ {int waterlevel; TYPE_3__* ps; TYPE_4__ cmd; } ;
struct TYPE_8__ {int /*<<< orphan*/  normal; } ;
struct TYPE_9__ {int surfaceFlags; TYPE_1__ plane; } ;
struct TYPE_12__ {float* forward; float* right; int frametime; TYPE_2__ groundTrace; } ;
struct TYPE_10__ {int pm_flags; float speed; float* velocity; int gravity; } ;

/* Variables and functions */
 scalar_t__ DotProduct (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVERCLIP ; 
 int PMF_DUCKED ; 
 int PMF_TIME_KNOCKBACK ; 
 int /*<<< orphan*/  PM_Accelerate (float*,float,float) ; 
 int /*<<< orphan*/  PM_AirMove () ; 
 scalar_t__ PM_CheckJump () ; 
 int /*<<< orphan*/  PM_ClipVelocity (float*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 float PM_CmdScale (TYPE_4__*) ; 
 int /*<<< orphan*/  PM_Friction () ; 
 int /*<<< orphan*/  PM_SetMovementDir () ; 
 int /*<<< orphan*/  PM_StepSlideMove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_WaterMove () ; 
 int SURF_SLICK ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (float*) ; 
 float VectorNormalize (float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 TYPE_6__* pm ; 
 float pm_accelerate ; 
 float pm_airaccelerate ; 
 float pm_duckScale ; 
 double pm_swimScale ; 
 TYPE_5__ pml ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void PM_WalkMove( void ) {
	int			i;
	vec3_t		wishvel;
	float		fmove, smove;
	vec3_t		wishdir;
	float		wishspeed;
	float		scale;
	usercmd_t	cmd;
	float		accelerate;
	float		vel;

	if ( pm->waterlevel > 2 && DotProduct( pml.forward, pml.groundTrace.plane.normal ) > 0 ) {
		// begin swimming
		PM_WaterMove();
		return;
	}


	if ( PM_CheckJump () ) {
		// jumped away
		if ( pm->waterlevel > 1 ) {
			PM_WaterMove();
		} else {
			PM_AirMove();
		}
		return;
	}

	PM_Friction ();

	fmove = pm->cmd.forwardmove;
	smove = pm->cmd.rightmove;

	cmd = pm->cmd;
	scale = PM_CmdScale( &cmd );

	// set the movementDir so clients can rotate the legs for strafing
	PM_SetMovementDir();

	// project moves down to flat plane
	pml.forward[2] = 0;
	pml.right[2] = 0;

	// project the forward and right directions onto the ground plane
	PM_ClipVelocity (pml.forward, pml.groundTrace.plane.normal, pml.forward, OVERCLIP );
	PM_ClipVelocity (pml.right, pml.groundTrace.plane.normal, pml.right, OVERCLIP );
	//
	VectorNormalize (pml.forward);
	VectorNormalize (pml.right);

	for ( i = 0 ; i < 3 ; i++ ) {
		wishvel[i] = pml.forward[i]*fmove + pml.right[i]*smove;
	}
	// when going up or down slopes the wish velocity should Not be zero
//	wishvel[2] = 0;

	VectorCopy (wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);
	wishspeed *= scale;

	// clamp the speed lower if ducking
	if ( pm->ps->pm_flags & PMF_DUCKED ) {
		if ( wishspeed > pm->ps->speed * pm_duckScale ) {
			wishspeed = pm->ps->speed * pm_duckScale;
		}
	}

	// clamp the speed lower if wading or walking on the bottom
	if ( pm->waterlevel ) {
		float	waterScale;

		waterScale = pm->waterlevel / 3.0;
		waterScale = 1.0 - ( 1.0 - pm_swimScale ) * waterScale;
		if ( wishspeed > pm->ps->speed * waterScale ) {
			wishspeed = pm->ps->speed * waterScale;
		}
	}

	// when a player gets hit, they temporarily lose
	// full control, which allows them to be moved a bit
	if ( ( pml.groundTrace.surfaceFlags & SURF_SLICK ) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK ) {
		accelerate = pm_airaccelerate;
	} else {
		accelerate = pm_accelerate;
	}

	PM_Accelerate (wishdir, wishspeed, accelerate);

	//Com_Printf("velocity = %1.1f %1.1f %1.1f\n", pm->ps->velocity[0], pm->ps->velocity[1], pm->ps->velocity[2]);
	//Com_Printf("velocity1 = %1.1f\n", VectorLength(pm->ps->velocity));

	if ( ( pml.groundTrace.surfaceFlags & SURF_SLICK ) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK ) {
		pm->ps->velocity[2] -= pm->ps->gravity * pml.frametime;
	} else {
		// don't reset the z velocity for slopes
//		pm->ps->velocity[2] = 0;
	}

	vel = VectorLength(pm->ps->velocity);

	// slide along the ground plane
	PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal, 
		pm->ps->velocity, OVERCLIP );

	// don't decrease velocity when going up or down a slope
	VectorNormalize(pm->ps->velocity);
	VectorScale(pm->ps->velocity, vel, pm->ps->velocity);

	// don't do anything if standing still
	if (!pm->ps->velocity[0] && !pm->ps->velocity[1]) {
		return;
	}

	PM_StepSlideMove( qfalse );

	//Com_Printf("velocity2 = %1.1f\n", VectorLength(pm->ps->velocity));

}