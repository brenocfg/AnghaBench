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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int oldFrame; int frame; float backlerp; scalar_t__ yawing; } ;
struct TYPE_8__ {scalar_t__ legsAnimationTimer; int legsAnim; scalar_t__ torsoAnimationTimer; int torsoAnim; TYPE_5__ torso; TYPE_5__ legs; } ;
typedef  TYPE_1__ playerInfo_t ;
struct TYPE_9__ {scalar_t__ frametime; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int LEGS_IDLE ; 
 int LEGS_TURN ; 
 int /*<<< orphan*/  UI_LegsSequencing (TYPE_1__*) ; 
 int /*<<< orphan*/  UI_RunLerpFrame (TYPE_1__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  UI_TorsoSequencing (TYPE_1__*) ; 
 TYPE_2__ uis ; 

__attribute__((used)) static void UI_PlayerAnimation( playerInfo_t *pi, int *legsOld, int *legs, float *legsBackLerp,
						int *torsoOld, int *torso, float *torsoBackLerp ) {

	// legs animation
	pi->legsAnimationTimer -= uis.frametime;
	if ( pi->legsAnimationTimer < 0 ) {
		pi->legsAnimationTimer = 0;
	}

	UI_LegsSequencing( pi );

	if ( pi->legs.yawing && ( pi->legsAnim & ~ANIM_TOGGLEBIT ) == LEGS_IDLE ) {
		UI_RunLerpFrame( pi, &pi->legs, LEGS_TURN );
	} else {
		UI_RunLerpFrame( pi, &pi->legs, pi->legsAnim );
	}
	*legsOld = pi->legs.oldFrame;
	*legs = pi->legs.frame;
	*legsBackLerp = pi->legs.backlerp;

	// torso animation
	pi->torsoAnimationTimer -= uis.frametime;
	if ( pi->torsoAnimationTimer < 0 ) {
		pi->torsoAnimationTimer = 0;
	}

	UI_TorsoSequencing( pi );

	UI_RunLerpFrame( pi, &pi->torso, pi->torsoAnim );
	*torsoOld = pi->torso.oldFrame;
	*torso = pi->torso.frame;
	*torsoBackLerp = pi->torso.backlerp;
}