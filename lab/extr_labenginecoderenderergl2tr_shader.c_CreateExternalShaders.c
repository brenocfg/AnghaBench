#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  image_t ;
struct TYPE_14__ {scalar_t__ defaultShader; } ;
struct TYPE_13__ {int /*<<< orphan*/  stateBits; int /*<<< orphan*/  active; TYPE_4__* bundle; } ;
struct TYPE_12__ {TYPE_7__* sunFlareShader; int /*<<< orphan*/ * dlightImage; TYPE_3__* flareShader; void* sunShader; void* projectionShadowShader; } ;
struct TYPE_11__ {int /*<<< orphan*/ ** image; } ;
struct TYPE_10__ {int numUnfoggedPasses; TYPE_2__** stages; int /*<<< orphan*/  defaultShader; } ;
struct TYPE_9__ {TYPE_1__* bundle; int /*<<< orphan*/  stateBits; int /*<<< orphan*/  adjustColorsForFog; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** image; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACFF_NONE ; 
 TYPE_7__* FinishShader () ; 
 int /*<<< orphan*/  GLS_DEFAULT ; 
 int /*<<< orphan*/  GLS_DEPTHTEST_DISABLE ; 
 int /*<<< orphan*/  InitShader (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIGHTMAP_NONE ; 
 void* R_FindShader (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_6__* stages ; 
 TYPE_5__ tr ; 

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

	tr.sunFlareShader = R_FindShader( "gfx/2d/sunflare", LIGHTMAP_NONE, qtrue);

	// HACK: if sunflare is missing, make one using the flare image or dlight image
	if (tr.sunFlareShader->defaultShader)
	{
		image_t *image;

		if (!tr.flareShader->defaultShader && tr.flareShader->stages[0] && tr.flareShader->stages[0]->bundle[0].image[0])
			image = tr.flareShader->stages[0]->bundle[0].image[0];
		else
			image = tr.dlightImage;

		InitShader( "gfx/2d/sunflare", LIGHTMAP_NONE );
		stages[0].bundle[0].image[0] = image;
		stages[0].active = qtrue;
		stages[0].stateBits = GLS_DEFAULT;
		tr.sunFlareShader = FinishShader();
	}

}