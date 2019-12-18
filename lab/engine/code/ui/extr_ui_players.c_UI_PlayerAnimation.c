#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int oldFrame; int frame; float backlerp; scalar_t__ yawing; } ;
struct TYPE_10__ {scalar_t__ legsAnimationTimer; int legsAnim; scalar_t__ torsoAnimationTimer; int torsoAnim; TYPE_6__ torso; TYPE_6__ legs; } ;
typedef  TYPE_2__ playerInfo_t ;
struct TYPE_9__ {scalar_t__ frameTime; } ;
struct TYPE_11__ {TYPE_1__ uiDC; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int LEGS_IDLE ; 
 int LEGS_TURN ; 
 int /*<<< orphan*/  UI_LegsSequencing (TYPE_2__*) ; 
 int /*<<< orphan*/  UI_RunLerpFrame (TYPE_2__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  UI_TorsoSequencing (TYPE_2__*) ; 
 TYPE_3__ uiInfo ; 

__attribute__((used)) static void UI_PlayerAnimation( playerInfo_t *pi, int *legsOld, int *legs, float *legsBackLerp,
						int *torsoOld, int *torso, float *torsoBackLerp ) {

	// legs animation
	pi->legsAnimationTimer -= uiInfo.uiDC.frameTime;
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
	pi->torsoAnimationTimer -= uiInfo.uiDC.frameTime;
	if ( pi->torsoAnimationTimer < 0 ) {
		pi->torsoAnimationTimer = 0;
	}

	UI_TorsoSequencing( pi );

	UI_RunLerpFrame( pi, &pi->torso, pi->torsoAnim );
	*torsoOld = pi->torso.oldFrame;
	*torso = pi->torso.frame;
	*torsoBackLerp = pi->torso.backlerp;
}