#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_14__ {float shaderTime; int* origin; int* oldorigin; int* shaderRGBA; float radius; int /*<<< orphan*/  customShader; int /*<<< orphan*/  reType; int /*<<< orphan*/  axis; } ;
typedef  TYPE_3__ refEntity_t ;
struct TYPE_12__ {float trTime; int* trBase; int* trDelta; int /*<<< orphan*/  trType; } ;
struct TYPE_15__ {float startTime; double endTime; double lifeRate; double* color; TYPE_1__ pos; int /*<<< orphan*/  leType; int /*<<< orphan*/  leFlags; TYPE_3__ refEntity; } ;
typedef  TYPE_4__ localEntity_t ;
struct TYPE_16__ {int* color1; int* color2; } ;
typedef  TYPE_5__ clientInfo_t ;
struct TYPE_20__ {float time; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {double value; } ;
struct TYPE_13__ {int /*<<< orphan*/  railRingsShader; int /*<<< orphan*/  railCoreShader; } ;
struct TYPE_17__ {TYPE_2__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  AxisClear (int /*<<< orphan*/ ) ; 
 TYPE_4__* CG_AllocLocalEntity () ; 
 int /*<<< orphan*/  LEF_PUFF_DONT_SCALE ; 
 int /*<<< orphan*/  LE_FADE_RGB ; 
 int /*<<< orphan*/  LE_MOVE_SCALE_FADE ; 
 int /*<<< orphan*/  PerpendicularVector (int*,int*) ; 
 int RADIUS ; 
 int ROTATION ; 
 int /*<<< orphan*/  RT_RAIL_CORE ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  RotatePointAroundVector (int*,int*,int*,int) ; 
 int SPACING ; 
 int /*<<< orphan*/  TR_LINEAR ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 float VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,int,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 TYPE_9__ cg ; 
 TYPE_8__ cg_oldRail ; 
 TYPE_7__ cg_railTrailTime ; 
 TYPE_6__ cgs ; 

void CG_RailTrail (clientInfo_t *ci, vec3_t start, vec3_t end) {
	vec3_t axis[36], move, move2, vec, temp;
	float  len;
	int    i, j, skip;
 
	localEntity_t *le;
	refEntity_t   *re;
 
#define RADIUS   4
#define ROTATION 1
#define SPACING  5
 
	start[2] -= 4;
 
	le = CG_AllocLocalEntity();
	re = &le->refEntity;
 
	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + cg_railTrailTime.value;
	le->lifeRate = 1.0 / (le->endTime - le->startTime);
 
	re->shaderTime = cg.time / 1000.0f;
	re->reType = RT_RAIL_CORE;
	re->customShader = cgs.media.railCoreShader;
 
	VectorCopy(start, re->origin);
	VectorCopy(end, re->oldorigin);
 
	re->shaderRGBA[0] = ci->color1[0] * 255;
	re->shaderRGBA[1] = ci->color1[1] * 255;
	re->shaderRGBA[2] = ci->color1[2] * 255;
	re->shaderRGBA[3] = 255;

	le->color[0] = ci->color1[0] * 0.75;
	le->color[1] = ci->color1[1] * 0.75;
	le->color[2] = ci->color1[2] * 0.75;
	le->color[3] = 1.0f;

	AxisClear( re->axis );
 
	if (cg_oldRail.integer)
	{
		// nudge down a bit so it isn't exactly in center
		re->origin[2] -= 8;
		re->oldorigin[2] -= 8;
		return;
	}

	VectorCopy (start, move);
	VectorSubtract (end, start, vec);
	len = VectorNormalize (vec);
	PerpendicularVector(temp, vec);
	for (i = 0 ; i < 36; i++)
	{
		RotatePointAroundVector(axis[i], vec, temp, i * 10);//banshee 2.4 was 10
	}

	VectorMA(move, 20, vec, move);
	VectorScale (vec, SPACING, vec);

	skip = -1;
 
	j = 18;
	for (i = 0; i < len; i += SPACING)
	{
		if (i != skip)
		{
			skip = i + SPACING;
			le = CG_AllocLocalEntity();
			re = &le->refEntity;
			le->leFlags = LEF_PUFF_DONT_SCALE;
			le->leType = LE_MOVE_SCALE_FADE;
			le->startTime = cg.time;
			le->endTime = cg.time + (i>>1) + 600;
			le->lifeRate = 1.0 / (le->endTime - le->startTime);

			re->shaderTime = cg.time / 1000.0f;
			re->reType = RT_SPRITE;
			re->radius = 1.1f;
			re->customShader = cgs.media.railRingsShader;

			re->shaderRGBA[0] = ci->color2[0] * 255;
			re->shaderRGBA[1] = ci->color2[1] * 255;
			re->shaderRGBA[2] = ci->color2[2] * 255;
			re->shaderRGBA[3] = 255;

			le->color[0] = ci->color2[0] * 0.75;
			le->color[1] = ci->color2[1] * 0.75;
			le->color[2] = ci->color2[2] * 0.75;
			le->color[3] = 1.0f;

			le->pos.trType = TR_LINEAR;
			le->pos.trTime = cg.time;

			VectorCopy( move, move2);
			VectorMA(move2, RADIUS , axis[j], move2);
			VectorCopy(move2, le->pos.trBase);

			le->pos.trDelta[0] = axis[j][0]*6;
			le->pos.trDelta[1] = axis[j][1]*6;
			le->pos.trDelta[2] = axis[j][2]*6;
		}

		VectorAdd (move, vec, move);

		j = (j + ROTATION) % 36;
	}
}