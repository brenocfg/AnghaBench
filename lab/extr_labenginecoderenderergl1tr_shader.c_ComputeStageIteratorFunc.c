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
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int numUnfoggedPasses; int /*<<< orphan*/  optimalStageIteratorFunc; scalar_t__ multitextureEnv; int /*<<< orphan*/  numDeforms; int /*<<< orphan*/  polygonOffset; scalar_t__ isSky; } ;
struct TYPE_6__ {scalar_t__ rgbGen; scalar_t__ alphaGen; TYPE_1__* bundle; } ;
struct TYPE_5__ {scalar_t__ tcGen; } ;

/* Variables and functions */
 scalar_t__ AGEN_IDENTITY ; 
 scalar_t__ CGEN_IDENTITY ; 
 scalar_t__ CGEN_LIGHTING_DIFFUSE ; 
 int /*<<< orphan*/  RB_StageIteratorGeneric ; 
 int /*<<< orphan*/  RB_StageIteratorLightmappedMultitexture ; 
 int /*<<< orphan*/  RB_StageIteratorSky ; 
 int /*<<< orphan*/  RB_StageIteratorVertexLitTexture ; 
 scalar_t__ TCGEN_LIGHTMAP ; 
 scalar_t__ TCGEN_TEXTURE ; 
 TYPE_4__* r_ignoreFastPath ; 
 TYPE_3__ shader ; 
 TYPE_2__* stages ; 

__attribute__((used)) static void ComputeStageIteratorFunc( void )
{
	shader.optimalStageIteratorFunc = RB_StageIteratorGeneric;

	//
	// see if this should go into the sky path
	//
	if ( shader.isSky )
	{
		shader.optimalStageIteratorFunc = RB_StageIteratorSky;
		return;
	}

	if ( r_ignoreFastPath->integer )
	{
		return;
	}

	//
	// see if this can go into the vertex lit fast path
	//
	if ( shader.numUnfoggedPasses == 1 )
	{
		if ( stages[0].rgbGen == CGEN_LIGHTING_DIFFUSE )
		{
			if ( stages[0].alphaGen == AGEN_IDENTITY )
			{
				if ( stages[0].bundle[0].tcGen == TCGEN_TEXTURE )
				{
					if ( !shader.polygonOffset )
					{
						if ( !shader.multitextureEnv )
						{
							if ( !shader.numDeforms )
							{
								shader.optimalStageIteratorFunc = RB_StageIteratorVertexLitTexture;
								return;
							}
						}
					}
				}
			}
		}
	}

	//
	// see if this can go into an optimized LM, multitextured path
	//
	if ( shader.numUnfoggedPasses == 1 )
	{
		if ( ( stages[0].rgbGen == CGEN_IDENTITY ) && ( stages[0].alphaGen == AGEN_IDENTITY ) )
		{
			if ( stages[0].bundle[0].tcGen == TCGEN_TEXTURE && 
				stages[0].bundle[1].tcGen == TCGEN_LIGHTMAP )
			{
				if ( !shader.polygonOffset )
				{
					if ( !shader.numDeforms )
					{
						if ( shader.multitextureEnv )
						{
							shader.optimalStageIteratorFunc = RB_StageIteratorLightmappedMultitexture;
						}
					}
				}
			}
		}
	}
}