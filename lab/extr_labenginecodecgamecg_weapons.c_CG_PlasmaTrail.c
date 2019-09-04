#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int* flashDlightColor; } ;
typedef  TYPE_4__ weaponInfo_t ;
typedef  int* vec3_t ;
struct TYPE_23__ {float shaderTime; float radius; int* shaderRGBA; int /*<<< orphan*/  customShader; int /*<<< orphan*/  reType; int /*<<< orphan*/  axis; int /*<<< orphan*/  origin; } ;
typedef  TYPE_5__ refEntity_t ;
struct TYPE_20__ {float trTime; int* trBase; int* trDelta; int /*<<< orphan*/  trType; } ;
struct TYPE_21__ {float trTime; int /*<<< orphan*/  trDelta; int /*<<< orphan*/  trBase; int /*<<< orphan*/  trType; } ;
struct TYPE_24__ {float startTime; float endTime; float bounceFactor; double* color; TYPE_2__ angles; TYPE_3__ pos; int /*<<< orphan*/  leMarkType; int /*<<< orphan*/  leBounceSoundType; int /*<<< orphan*/  leFlags; int /*<<< orphan*/  leType; TYPE_5__ refEntity; } ;
typedef  TYPE_6__ localEntity_t ;
struct TYPE_25__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_7__ entityState_t ;
struct TYPE_26__ {int /*<<< orphan*/  lerpAngles; TYPE_7__ currentState; } ;
typedef  TYPE_8__ centity_t ;
struct TYPE_19__ {int /*<<< orphan*/  railRingsShader; } ;
struct TYPE_27__ {TYPE_1__ media; } ;
struct TYPE_18__ {float time; } ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  AxisCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BG_EvaluateTrajectory (int /*<<< orphan*/ *,float,int*) ; 
 TYPE_6__* CG_AllocLocalEntity () ; 
 int CG_PointContents (int /*<<< orphan*/ ,int) ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  LEBS_NONE ; 
 int /*<<< orphan*/  LEF_TUMBLE ; 
 int /*<<< orphan*/  LEMT_NONE ; 
 int /*<<< orphan*/  LE_MOVE_SCALE_FADE ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  TR_GRAVITY ; 
 int /*<<< orphan*/  TR_LINEAR ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axisDefault ; 
 TYPE_12__ cg ; 
 TYPE_11__ cg_noProjectileTrail ; 
 TYPE_10__ cg_oldPlasma ; 
 TYPE_9__ cgs ; 
 int crandom () ; 
 int rand () ; 

__attribute__((used)) static void CG_PlasmaTrail( centity_t *cent, const weaponInfo_t *wi ) {
	localEntity_t	*le;
	refEntity_t		*re;
	entityState_t	*es;
	vec3_t			velocity, xvelocity, origin;
	vec3_t			offset, xoffset;
	vec3_t			v[3];

	float	waterScale = 1.0f;

	if ( cg_noProjectileTrail.integer || cg_oldPlasma.integer ) {
		return;
	}

	es = &cent->currentState;

	BG_EvaluateTrajectory( &es->pos, cg.time, origin );

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	velocity[0] = 60 - 120 * crandom();
	velocity[1] = 40 - 80 * crandom();
	velocity[2] = 100 - 200 * crandom();

	le->leType = LE_MOVE_SCALE_FADE;
	le->leFlags = LEF_TUMBLE;
	le->leBounceSoundType = LEBS_NONE;
	le->leMarkType = LEMT_NONE;

	le->startTime = cg.time;
	le->endTime = le->startTime + 600;

	le->pos.trType = TR_GRAVITY;
	le->pos.trTime = cg.time;

	AnglesToAxis( cent->lerpAngles, v );

	offset[0] = 2;
	offset[1] = 2;
	offset[2] = 2;

	xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
	xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
	xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];

	VectorAdd( origin, xoffset, re->origin );
	VectorCopy( re->origin, le->pos.trBase );

	if ( CG_PointContents( re->origin, -1 ) & CONTENTS_WATER ) {
		waterScale = 0.10f;
	}

	xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
	xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
	xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
	VectorScale( xvelocity, waterScale, le->pos.trDelta );

	AxisCopy( axisDefault, re->axis );
	re->shaderTime = cg.time / 1000.0f;
	re->reType = RT_SPRITE;
	re->radius = 0.25f;
	re->customShader = cgs.media.railRingsShader;
	le->bounceFactor = 0.3f;

	re->shaderRGBA[0] = wi->flashDlightColor[0] * 63;
	re->shaderRGBA[1] = wi->flashDlightColor[1] * 63;
	re->shaderRGBA[2] = wi->flashDlightColor[2] * 63;
	re->shaderRGBA[3] = 63;

	le->color[0] = wi->flashDlightColor[0] * 0.2;
	le->color[1] = wi->flashDlightColor[1] * 0.2;
	le->color[2] = wi->flashDlightColor[2] * 0.2;
	le->color[3] = 0.25f;

	le->angles.trType = TR_LINEAR;
	le->angles.trTime = cg.time;
	le->angles.trBase[0] = rand()&31;
	le->angles.trBase[1] = rand()&31;
	le->angles.trBase[2] = rand()&31;
	le->angles.trDelta[0] = 1;
	le->angles.trDelta[1] = 0.5;
	le->angles.trDelta[2] = 0;

}