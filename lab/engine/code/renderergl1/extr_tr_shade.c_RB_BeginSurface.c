#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ timeOffset; scalar_t__ clampTime; int /*<<< orphan*/  optimalStageIteratorFunc; int /*<<< orphan*/  numUnfoggedPasses; int /*<<< orphan*/  stages; struct TYPE_7__* remappedShader; } ;
typedef  TYPE_2__ shader_t ;
struct TYPE_6__ {scalar_t__ floatTime; } ;
struct TYPE_9__ {TYPE_1__ refdef; } ;
struct TYPE_8__ {int fogNum; scalar_t__ shaderTime; TYPE_2__* shader; int /*<<< orphan*/  currentStageIteratorFunc; int /*<<< orphan*/  numPasses; int /*<<< orphan*/  xstages; scalar_t__ dlightBits; scalar_t__ numVertexes; scalar_t__ numIndexes; } ;

/* Variables and functions */
 TYPE_4__ backEnd ; 
 TYPE_3__ tess ; 

void RB_BeginSurface( shader_t *shader, int fogNum ) {

	shader_t *state = (shader->remappedShader) ? shader->remappedShader : shader;

	tess.numIndexes = 0;
	tess.numVertexes = 0;
	tess.shader = state;
	tess.fogNum = fogNum;
	tess.dlightBits = 0;		// will be OR'd in by surface functions
	tess.xstages = state->stages;
	tess.numPasses = state->numUnfoggedPasses;
	tess.currentStageIteratorFunc = state->optimalStageIteratorFunc;

	tess.shaderTime = backEnd.refdef.floatTime - tess.shader->timeOffset;
	if (tess.shader->clampTime && tess.shaderTime >= tess.shader->clampTime) {
		tess.shaderTime = tess.shader->clampTime;
	}


}