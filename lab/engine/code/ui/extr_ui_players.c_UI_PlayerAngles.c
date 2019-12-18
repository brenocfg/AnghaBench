#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_7__ {float yawAngle; float pitchAngle; void* pitching; void* yawing; } ;
struct TYPE_6__ {float yawAngle; void* yawing; } ;
struct TYPE_8__ {int legsAnim; int torsoAnim; scalar_t__ fixedlegs; scalar_t__ fixedtorso; TYPE_2__ torso; TYPE_1__ legs; int /*<<< orphan*/  viewAngles; } ;
typedef  TYPE_3__ playerInfo_t ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 float AngleMod (float) ; 
 int /*<<< orphan*/  AnglesSubtract (float*,float*,float*) ; 
 int /*<<< orphan*/  AnglesToAxis (float*,float**) ; 
 int LEGS_IDLE ; 
 size_t PITCH ; 
 size_t ROLL ; 
 float SWINGSPEED ; 
 int TORSO_STAND ; 
 float UI_MovedirAdjustment (TYPE_3__*) ; 
 int /*<<< orphan*/  UI_SwingAngles (float,int,int,float,float*,void**) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 size_t YAW ; 
 void* qtrue ; 

__attribute__((used)) static void UI_PlayerAngles( playerInfo_t *pi, vec3_t legs[3], vec3_t torso[3], vec3_t head[3] ) {
	vec3_t		legsAngles, torsoAngles, headAngles;
	float		dest;
	float		adjust;

	VectorCopy( pi->viewAngles, headAngles );
	headAngles[YAW] = AngleMod( headAngles[YAW] );
	VectorClear( legsAngles );
	VectorClear( torsoAngles );

	// --------- yaw -------------

	// allow yaw to drift a bit
	if ( ( pi->legsAnim & ~ANIM_TOGGLEBIT ) != LEGS_IDLE 
		|| ( pi->torsoAnim & ~ANIM_TOGGLEBIT ) != TORSO_STAND  ) {
		// if not standing still, always point all in the same direction
		pi->torso.yawing = qtrue;	// always center
		pi->torso.pitching = qtrue;	// always center
		pi->legs.yawing = qtrue;	// always center
	}

	// adjust legs for movement dir
	adjust = UI_MovedirAdjustment( pi );
	legsAngles[YAW] = headAngles[YAW] + adjust;
	torsoAngles[YAW] = headAngles[YAW] + 0.25 * adjust;


	// torso
	UI_SwingAngles( torsoAngles[YAW], 25, 90, SWINGSPEED, &pi->torso.yawAngle, &pi->torso.yawing );
	UI_SwingAngles( legsAngles[YAW], 40, 90, SWINGSPEED, &pi->legs.yawAngle, &pi->legs.yawing );

	torsoAngles[YAW] = pi->torso.yawAngle;
	legsAngles[YAW] = pi->legs.yawAngle;

	// --------- pitch -------------

	// only show a fraction of the pitch angle in the torso
	if ( headAngles[PITCH] > 180 ) {
		dest = (-360 + headAngles[PITCH]) * 0.75;
	} else {
		dest = headAngles[PITCH] * 0.75;
	}
	UI_SwingAngles( dest, 15, 30, 0.1f, &pi->torso.pitchAngle, &pi->torso.pitching );
	torsoAngles[PITCH] = pi->torso.pitchAngle;

	if ( pi->fixedtorso ) {
		torsoAngles[PITCH] = 0.0f;
	}

	if ( pi->fixedlegs ) {
		legsAngles[YAW] = torsoAngles[YAW];
		legsAngles[PITCH] = 0.0f;
		legsAngles[ROLL] = 0.0f;
	}

	// pull the angles back out of the hierarchial chain
	AnglesSubtract( headAngles, torsoAngles, headAngles );
	AnglesSubtract( torsoAngles, legsAngles, torsoAngles );
	AnglesToAxis( legsAngles, legs );
	AnglesToAxis( torsoAngles, torso );
	AnglesToAxis( headAngles, head );
}