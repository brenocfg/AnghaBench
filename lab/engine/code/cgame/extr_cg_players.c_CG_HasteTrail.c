#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_13__ {int /*<<< orphan*/  leType; } ;
typedef  TYPE_4__ localEntity_t ;
struct TYPE_10__ {int animationNumber; } ;
struct TYPE_11__ {TYPE_1__ legs; } ;
struct TYPE_14__ {scalar_t__ trailTime; int /*<<< orphan*/  lerpOrigin; TYPE_2__ pe; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_16__ {scalar_t__ time; } ;
struct TYPE_12__ {int /*<<< orphan*/  hastePuffShader; } ;
struct TYPE_15__ {TYPE_3__ media; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 TYPE_4__* CG_SmokePuff (int*,int /*<<< orphan*/ ,int,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LEGS_BACK ; 
 int LEGS_RUN ; 
 int /*<<< orphan*/  LE_SCALE_FADE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 TYPE_7__ cg ; 
 TYPE_6__ cgs ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void CG_HasteTrail( centity_t *cent ) {
	localEntity_t	*smoke;
	vec3_t			origin;
	int				anim;

	if ( cent->trailTime > cg.time ) {
		return;
	}
	anim = cent->pe.legs.animationNumber & ~ANIM_TOGGLEBIT;
	if ( anim != LEGS_RUN && anim != LEGS_BACK ) {
		return;
	}

	cent->trailTime += 100;
	if ( cent->trailTime < cg.time ) {
		cent->trailTime = cg.time;
	}

	VectorCopy( cent->lerpOrigin, origin );
	origin[2] -= 16;

	smoke = CG_SmokePuff( origin, vec3_origin, 
				  8, 
				  1, 1, 1, 1,
				  500, 
				  cg.time,
				  0,
				  0,
				  cgs.media.hastePuffShader );

	// use the optimized local entity add
	smoke->leType = LE_SCALE_FADE;
}