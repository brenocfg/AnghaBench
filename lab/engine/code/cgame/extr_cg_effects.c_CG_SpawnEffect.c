#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {float shaderTime; int* origin; int /*<<< orphan*/  axis; int /*<<< orphan*/  hModel; int /*<<< orphan*/  customShader; int /*<<< orphan*/  reType; } ;
typedef  TYPE_2__ refEntity_t ;
struct TYPE_9__ {double startTime; int endTime; double lifeRate; double* color; TYPE_2__ refEntity; int /*<<< orphan*/  leType; scalar_t__ leFlags; } ;
typedef  TYPE_3__ localEntity_t ;
struct TYPE_11__ {double time; } ;
struct TYPE_7__ {int /*<<< orphan*/  teleportEffectModel; int /*<<< orphan*/  teleportEffectShader; } ;
struct TYPE_10__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  AxisClear (int /*<<< orphan*/ ) ; 
 TYPE_3__* CG_AllocLocalEntity () ; 
 int /*<<< orphan*/  LE_FADE_RGB ; 
 int /*<<< orphan*/  RT_MODEL ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 TYPE_5__ cg ; 
 TYPE_4__ cgs ; 

void CG_SpawnEffect( vec3_t org ) {
	localEntity_t	*le;
	refEntity_t		*re;

	le = CG_AllocLocalEntity();
	le->leFlags = 0;
	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + 500;
	le->lifeRate = 1.0 / ( le->endTime - le->startTime );

	le->color[0] = le->color[1] = le->color[2] = le->color[3] = 1.0;

	re = &le->refEntity;

	re->reType = RT_MODEL;
	re->shaderTime = cg.time / 1000.0f;

#ifndef MISSIONPACK
	re->customShader = cgs.media.teleportEffectShader;
#endif
	re->hModel = cgs.media.teleportEffectModel;
	AxisClear( re->axis );

	VectorCopy( org, re->origin );
#ifdef MISSIONPACK
	re->origin[2] += 16;
#else
	re->origin[2] -= 24;
#endif
}