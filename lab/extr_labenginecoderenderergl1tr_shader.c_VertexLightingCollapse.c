#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ func; } ;
struct TYPE_9__ {scalar_t__ rgbGen; int stateBits; int /*<<< orphan*/  active; TYPE_2__ rgbWave; TYPE_1__* bundle; int /*<<< orphan*/  alphaGen; } ;
typedef  TYPE_3__ shaderStage_t ;
struct TYPE_10__ {scalar_t__ sort; scalar_t__ lightmapIndex; } ;
struct TYPE_7__ {scalar_t__ tcGen; scalar_t__ isLightmap; scalar_t__ numTexMods; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGEN_SKIP ; 
 scalar_t__ CGEN_EXACT_VERTEX ; 
 scalar_t__ CGEN_IDENTITY ; 
 scalar_t__ CGEN_IDENTITY_LIGHTING ; 
 scalar_t__ CGEN_LIGHTING_DIFFUSE ; 
 scalar_t__ CGEN_ONE_MINUS_ENTITY ; 
 scalar_t__ CGEN_WAVEFORM ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GF_INVERSE_SAWTOOTH ; 
 scalar_t__ GF_SAWTOOTH ; 
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_DSTBLEND_BITS ; 
 int GLS_SRCBLEND_BITS ; 
 scalar_t__ LIGHTMAP_NONE ; 
 int MAX_SHADER_STAGES ; 
 scalar_t__ SS_OPAQUE ; 
 scalar_t__ TCGEN_TEXTURE ; 
 TYPE_5__ shader ; 
 TYPE_3__* stages ; 

__attribute__((used)) static void VertexLightingCollapse( void ) {
	int		stage;
	shaderStage_t	*bestStage;
	int		bestImageRank;
	int		rank;

	// if we aren't opaque, just use the first pass
	if ( shader.sort == SS_OPAQUE ) {

		// pick the best texture for the single pass
		bestStage = &stages[0];
		bestImageRank = -999999;

		for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ ) {
			shaderStage_t *pStage = &stages[stage];

			if ( !pStage->active ) {
				break;
			}
			rank = 0;

			if ( pStage->bundle[0].isLightmap ) {
				rank -= 100;
			}
			if ( pStage->bundle[0].tcGen != TCGEN_TEXTURE ) {
				rank -= 5;
			}
			if ( pStage->bundle[0].numTexMods ) {
				rank -= 5;
			}
			if ( pStage->rgbGen != CGEN_IDENTITY && pStage->rgbGen != CGEN_IDENTITY_LIGHTING ) {
				rank -= 3;
			}

			if ( rank > bestImageRank  ) {
				bestImageRank = rank;
				bestStage = pStage;
			}
		}

		stages[0].bundle[0] = bestStage->bundle[0];
		stages[0].stateBits &= ~( GLS_DSTBLEND_BITS | GLS_SRCBLEND_BITS );
		stages[0].stateBits |= GLS_DEPTHMASK_TRUE;
		if ( shader.lightmapIndex == LIGHTMAP_NONE ) {
			stages[0].rgbGen = CGEN_LIGHTING_DIFFUSE;
		} else {
			stages[0].rgbGen = CGEN_EXACT_VERTEX;
		}
		stages[0].alphaGen = AGEN_SKIP;		
	} else {
		// don't use a lightmap (tesla coils)
		if ( stages[0].bundle[0].isLightmap ) {
			stages[0] = stages[1];
		}

		// if we were in a cross-fade cgen, hack it to normal
		if ( stages[0].rgbGen == CGEN_ONE_MINUS_ENTITY || stages[1].rgbGen == CGEN_ONE_MINUS_ENTITY ) {
			stages[0].rgbGen = CGEN_IDENTITY_LIGHTING;
		}
		if ( ( stages[0].rgbGen == CGEN_WAVEFORM && stages[0].rgbWave.func == GF_SAWTOOTH )
			&& ( stages[1].rgbGen == CGEN_WAVEFORM && stages[1].rgbWave.func == GF_INVERSE_SAWTOOTH ) ) {
			stages[0].rgbGen = CGEN_IDENTITY_LIGHTING;
		}
		if ( ( stages[0].rgbGen == CGEN_WAVEFORM && stages[0].rgbWave.func == GF_INVERSE_SAWTOOTH )
			&& ( stages[1].rgbGen == CGEN_WAVEFORM && stages[1].rgbWave.func == GF_SAWTOOTH ) ) {
			stages[0].rgbGen = CGEN_IDENTITY_LIGHTING;
		}
	}

	for ( stage = 1; stage < MAX_SHADER_STAGES; stage++ ) {
		shaderStage_t *pStage = &stages[stage];

		if ( !pStage->active ) {
			break;
		}

		Com_Memset( pStage, 0, sizeof( *pStage ) );
	}
}