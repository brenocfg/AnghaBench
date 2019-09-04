#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec5_t ;
struct TYPE_5__ {int func; int /*<<< orphan*/  frequency; int /*<<< orphan*/  phase; int /*<<< orphan*/  amplitude; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int deformation; int /*<<< orphan*/  bulgeSpeed; int /*<<< orphan*/  bulgeWidth; int /*<<< orphan*/  bulgeHeight; int /*<<< orphan*/  deformationSpread; TYPE_1__ deformationWave; } ;
typedef  TYPE_2__ deformStage_t ;
struct TYPE_8__ {TYPE_2__* deforms; } ;
struct TYPE_7__ {TYPE_4__* shader; } ;

/* Variables and functions */
#define  DEFORM_BULGE 129 
#define  DEFORM_WAVE 128 
 int DGEN_BULGE ; 
 int DGEN_NONE ; 
 int /*<<< orphan*/  ShaderRequiresCPUDeforms (TYPE_4__*) ; 
 TYPE_3__ tess ; 

__attribute__((used)) static void ComputeDeformValues(int *deformGen, vec5_t deformParams)
{
	// u_DeformGen
	*deformGen = DGEN_NONE;
	if(!ShaderRequiresCPUDeforms(tess.shader))
	{
		deformStage_t  *ds;

		// only support the first one
		ds = &tess.shader->deforms[0];

		switch (ds->deformation)
		{
			case DEFORM_WAVE:
				*deformGen = ds->deformationWave.func;

				deformParams[0] = ds->deformationWave.base;
				deformParams[1] = ds->deformationWave.amplitude;
				deformParams[2] = ds->deformationWave.phase;
				deformParams[3] = ds->deformationWave.frequency;
				deformParams[4] = ds->deformationSpread;
				break;

			case DEFORM_BULGE:
				*deformGen = DGEN_BULGE;

				deformParams[0] = 0;
				deformParams[1] = ds->bulgeHeight; // amplitude
				deformParams[2] = ds->bulgeWidth;  // phase
				deformParams[3] = ds->bulgeSpeed;  // frequency
				deformParams[4] = 0;
				break;

			default:
				break;
		}
	}
}