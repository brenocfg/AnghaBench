#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* sunShader; TYPE_2__* flareShader; void* projectionShadowShader; } ;
struct TYPE_5__ {int numUnfoggedPasses; TYPE_1__** stages; int /*<<< orphan*/  defaultShader; } ;
struct TYPE_4__ {int /*<<< orphan*/  stateBits; int /*<<< orphan*/  adjustColorsForFog; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACFF_NONE ; 
 int /*<<< orphan*/  GLS_DEPTHTEST_DISABLE ; 
 int /*<<< orphan*/  LIGHTMAP_NONE ; 
 void* R_FindShader (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__ tr ; 

__attribute__((used)) static void CreateExternalShaders( void ) {
	tr.projectionShadowShader = R_FindShader( "projectionShadow", LIGHTMAP_NONE, qtrue );
	tr.flareShader = R_FindShader( "flareShader", LIGHTMAP_NONE, qtrue );

	// Hack to make fogging work correctly on flares. Fog colors are calculated
	// in tr_flare.c already.
	if(!tr.flareShader->defaultShader)
	{
		int index;
		
		for(index = 0; index < tr.flareShader->numUnfoggedPasses; index++)
		{
			tr.flareShader->stages[index]->adjustColorsForFog = ACFF_NONE;
			tr.flareShader->stages[index]->stateBits |= GLS_DEPTHTEST_DISABLE;
		}
	}

	tr.sunShader = R_FindShader( "sun", LIGHTMAP_NONE, qtrue );
}