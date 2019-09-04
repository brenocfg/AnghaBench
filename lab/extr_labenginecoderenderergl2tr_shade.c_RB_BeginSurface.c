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
struct TYPE_9__ {scalar_t__ timeOffset; scalar_t__ clampTime; int /*<<< orphan*/  optimalStageIteratorFunc; int /*<<< orphan*/  numUnfoggedPasses; int /*<<< orphan*/  stages; struct TYPE_9__* remappedShader; } ;
typedef  TYPE_3__ shader_t ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {scalar_t__ floatTime; } ;
struct TYPE_11__ {TYPE_2__ viewParms; TYPE_1__ refdef; } ;
struct TYPE_10__ {int fogNum; int cubemapIndex; scalar_t__ shaderTime; int /*<<< orphan*/  currentStageIteratorFunc; TYPE_3__* shader; int /*<<< orphan*/  useCacheVao; int /*<<< orphan*/  useInternalVao; int /*<<< orphan*/  numPasses; int /*<<< orphan*/  xstages; scalar_t__ pshadowBits; scalar_t__ dlightBits; scalar_t__ numVertexes; scalar_t__ firstIndex; scalar_t__ numIndexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_StageIteratorGeneric ; 
 int VPF_SHADOWMAP ; 
 TYPE_5__ backEnd ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__ tess ; 

void RB_BeginSurface( shader_t *shader, int fogNum, int cubemapIndex ) {

	shader_t *state = (shader->remappedShader) ? shader->remappedShader : shader;

	tess.numIndexes = 0;
	tess.firstIndex = 0;
	tess.numVertexes = 0;
	tess.shader = state;
	tess.fogNum = fogNum;
	tess.cubemapIndex = cubemapIndex;
	tess.dlightBits = 0;		// will be OR'd in by surface functions
	tess.pshadowBits = 0;       // will be OR'd in by surface functions
	tess.xstages = state->stages;
	tess.numPasses = state->numUnfoggedPasses;
	tess.currentStageIteratorFunc = state->optimalStageIteratorFunc;
	tess.useInternalVao = qtrue;
	tess.useCacheVao = qfalse;

	tess.shaderTime = backEnd.refdef.floatTime - tess.shader->timeOffset;
	if (tess.shader->clampTime && tess.shaderTime >= tess.shader->clampTime) {
		tess.shaderTime = tess.shader->clampTime;
	}

	if (backEnd.viewParms.flags & VPF_SHADOWMAP)
	{
		tess.currentStageIteratorFunc = RB_StageIteratorGeneric;
	}
}