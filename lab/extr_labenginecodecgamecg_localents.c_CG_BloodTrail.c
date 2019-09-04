#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int* trDelta; } ;
struct TYPE_9__ {TYPE_7__ pos; int /*<<< orphan*/  leType; } ;
typedef  TYPE_2__ localEntity_t ;
struct TYPE_11__ {int time; int frametime; } ;
struct TYPE_8__ {int /*<<< orphan*/  bloodTrailShader; } ;
struct TYPE_10__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectory (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* CG_SmokePuff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LE_FALL_SCALE_FADE ; 
 TYPE_4__ cg ; 
 TYPE_3__ cgs ; 
 int /*<<< orphan*/  vec3_origin ; 

void CG_BloodTrail( localEntity_t *le ) {
	int		t;
	int		t2;
	int		step;
	vec3_t	newOrigin;
	localEntity_t	*blood;

	step = 150;
	t = step * ( (cg.time - cg.frametime + step ) / step );
	t2 = step * ( cg.time / step );

	for ( ; t <= t2; t += step ) {
		BG_EvaluateTrajectory( &le->pos, t, newOrigin );

		blood = CG_SmokePuff( newOrigin, vec3_origin, 
					  20,		// radius
					  1, 1, 1, 1,	// color
					  2000,		// trailTime
					  t,		// startTime
					  0,		// fadeInTime
					  0,		// flags
					  cgs.media.bloodTrailShader );
		// use the optimized version
		blood->leType = LE_FALL_SCALE_FADE;
		// drop a total of 40 units over its lifetime
		blood->pos.trDelta[2] = 40;
	}
}