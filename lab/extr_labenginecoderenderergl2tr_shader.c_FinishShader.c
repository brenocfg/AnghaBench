#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shader_t ;
struct TYPE_15__ {int stateBits; int /*<<< orphan*/  adjustColorsForFog; TYPE_1__* bundle; void* active; scalar_t__ isDetail; } ;
typedef  TYPE_2__ shaderStage_t ;
typedef  void* qboolean ;
struct TYPE_20__ {int /*<<< orphan*/  integer; } ;
struct TYPE_19__ {int /*<<< orphan*/  integer; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {scalar_t__ lightmapIndex; int numUnfoggedPasses; scalar_t__ sort; scalar_t__ isSky; int /*<<< orphan*/  name; scalar_t__ polygonOffset; } ;
struct TYPE_14__ {scalar_t__ tcGen; scalar_t__ isLightmap; int /*<<< orphan*/ * image; } ;
struct TYPE_13__ {scalar_t__ hardwareType; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACFF_MODULATE_ALPHA ; 
 int /*<<< orphan*/  ACFF_MODULATE_RGB ; 
 int /*<<< orphan*/  ACFF_MODULATE_RGBA ; 
 int CollapseStagesToGLSL () ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComputeStageIteratorFunc () ; 
 int /*<<< orphan*/  ComputeVertexAttribs () ; 
 scalar_t__ GLHW_PERMEDIA2 ; 
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_DSTBLEND_BITS ; 
 int GLS_DSTBLEND_ONE ; 
 int GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ; 
 int GLS_DSTBLEND_ONE_MINUS_SRC_COLOR ; 
 int GLS_SRCBLEND_BITS ; 
 int GLS_SRCBLEND_ONE ; 
 int GLS_SRCBLEND_SRC_ALPHA ; 
 int GLS_SRCBLEND_ZERO ; 
 int /*<<< orphan*/ * GeneratePermanentShader () ; 
 int MAX_SHADER_STAGES ; 
 int /*<<< orphan*/  PRINT_DEVELOPER ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 scalar_t__ SS_BLEND0 ; 
 scalar_t__ SS_DECAL ; 
 scalar_t__ SS_ENVIRONMENT ; 
 scalar_t__ SS_FOG ; 
 scalar_t__ SS_OPAQUE ; 
 scalar_t__ SS_SEE_THROUGH ; 
 scalar_t__ TCGEN_BAD ; 
 scalar_t__ TCGEN_LIGHTMAP ; 
 scalar_t__ TCGEN_TEXTURE ; 
 int /*<<< orphan*/  VertexLightingCollapse () ; 
 TYPE_11__ glConfig ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_8__* r_detailTextures ; 
 TYPE_7__* r_uiFullScreen ; 
 TYPE_6__* r_vertexLight ; 
 TYPE_5__ ri ; 
 TYPE_4__ shader ; 
 TYPE_2__* stages ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static shader_t *FinishShader( void ) {
	int stage;
	qboolean		hasLightmapStage;
	qboolean		vertexLightmap;

	hasLightmapStage = qfalse;
	vertexLightmap = qfalse;

	//
	// set sky stuff appropriate
	//
	if ( shader.isSky ) {
		shader.sort = SS_ENVIRONMENT;
	}

	//
	// set polygon offset
	//
	if ( shader.polygonOffset && !shader.sort ) {
		shader.sort = SS_DECAL;
	}

	//
	// set appropriate stage information
	//
	for ( stage = 0; stage < MAX_SHADER_STAGES; ) {
		shaderStage_t *pStage = &stages[stage];

		if ( !pStage->active ) {
			break;
		}

    // check for a missing texture
		if ( !pStage->bundle[0].image[0] ) {
			ri.Printf( PRINT_WARNING, "Shader %s has a stage with no image\n", shader.name );
			pStage->active = qfalse;
			stage++;
			continue;
		}

		//
		// ditch this stage if it's detail and detail textures are disabled
		//
		if ( pStage->isDetail && !r_detailTextures->integer )
		{
			int index;
			
			for(index = stage + 1; index < MAX_SHADER_STAGES; index++)
			{
				if(!stages[index].active)
					break;
			}
			
			if(index < MAX_SHADER_STAGES)
				memmove(pStage, pStage + 1, sizeof(*pStage) * (index - stage));
			else
			{
				if(stage + 1 < MAX_SHADER_STAGES)
					memmove(pStage, pStage + 1, sizeof(*pStage) * (index - stage - 1));
				
				Com_Memset(&stages[index - 1], 0, sizeof(*stages));
			}
			
			continue;
		}

		//
		// default texture coordinate generation
		//
		if ( pStage->bundle[0].isLightmap ) {
			if ( pStage->bundle[0].tcGen == TCGEN_BAD ) {
				pStage->bundle[0].tcGen = TCGEN_LIGHTMAP;
			}
			hasLightmapStage = qtrue;
		} else {
			if ( pStage->bundle[0].tcGen == TCGEN_BAD ) {
				pStage->bundle[0].tcGen = TCGEN_TEXTURE;
			}
		}


    // not a true lightmap but we want to leave existing 
    // behaviour in place and not print out a warning
    //if (pStage->rgbGen == CGEN_VERTEX) {
    //  vertexLightmap = qtrue;
    //}



		//
		// determine sort order and fog color adjustment
		//
		if ( ( pStage->stateBits & ( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS ) ) &&
			 ( stages[0].stateBits & ( GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS ) ) ) {
			int blendSrcBits = pStage->stateBits & GLS_SRCBLEND_BITS;
			int blendDstBits = pStage->stateBits & GLS_DSTBLEND_BITS;

			// fog color adjustment only works for blend modes that have a contribution
			// that aproaches 0 as the modulate values aproach 0 --
			// GL_ONE, GL_ONE
			// GL_ZERO, GL_ONE_MINUS_SRC_COLOR
			// GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA

			// modulate, additive
			if ( ( ( blendSrcBits == GLS_SRCBLEND_ONE ) && ( blendDstBits == GLS_DSTBLEND_ONE ) ) ||
				( ( blendSrcBits == GLS_SRCBLEND_ZERO ) && ( blendDstBits == GLS_DSTBLEND_ONE_MINUS_SRC_COLOR ) ) ) {
				pStage->adjustColorsForFog = ACFF_MODULATE_RGB;
			}
			// strict blend
			else if ( ( blendSrcBits == GLS_SRCBLEND_SRC_ALPHA ) && ( blendDstBits == GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ) )
			{
				pStage->adjustColorsForFog = ACFF_MODULATE_ALPHA;
			}
			// premultiplied alpha
			else if ( ( blendSrcBits == GLS_SRCBLEND_ONE ) && ( blendDstBits == GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ) )
			{
				pStage->adjustColorsForFog = ACFF_MODULATE_RGBA;
			} else {
				// we can't adjust this one correctly, so it won't be exactly correct in fog
			}

			// don't screw with sort order if this is a portal or environment
			if ( !shader.sort ) {
				// see through item, like a grill or grate
				if ( pStage->stateBits & GLS_DEPTHMASK_TRUE ) {
					shader.sort = SS_SEE_THROUGH;
				} else {
					shader.sort = SS_BLEND0;
				}
			}
		}
		
		stage++;
	}

	// there are times when you will need to manually apply a sort to
	// opaque alpha tested shaders that have later blend passes
	if ( !shader.sort ) {
		shader.sort = SS_OPAQUE;
	}

	//
	// if we are in r_vertexLight mode, never use a lightmap texture
	//
	if ( stage > 1 && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) ) {
		VertexLightingCollapse();
		hasLightmapStage = qfalse;
	}

	//
	// look for multitexture potential
	//
	stage = CollapseStagesToGLSL();

	if ( shader.lightmapIndex >= 0 && !hasLightmapStage ) {
		if (vertexLightmap) {
			ri.Printf( PRINT_DEVELOPER, "WARNING: shader '%s' has VERTEX forced lightmap!\n", shader.name );
		} else {
			ri.Printf( PRINT_DEVELOPER, "WARNING: shader '%s' has lightmap but no lightmap stage!\n", shader.name );
			// Don't set this, it will just add duplicate shaders to the hash
  			//shader.lightmapIndex = LIGHTMAP_NONE;
		}
	}


	//
	// compute number of passes
	//
	shader.numUnfoggedPasses = stage;

	// fogonly shaders don't have any normal passes
	if (stage == 0 && !shader.isSky)
		shader.sort = SS_FOG;

	// determine which stage iterator function is appropriate
	ComputeStageIteratorFunc();

	// determine which vertex attributes this shader needs
	ComputeVertexAttribs();

	return GeneratePermanentShader();
}