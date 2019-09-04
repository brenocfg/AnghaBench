#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int lightmapIndex; int /*<<< orphan*/  index; int /*<<< orphan*/  name; scalar_t__ defaultShader; struct TYPE_9__* next; } ;
typedef  TYPE_2__ shader_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  image_t ;
struct TYPE_12__ {int lightmapIndex; void* needsColor; void* needsST2; void* needsST1; void* needsNormal; } ;
struct TYPE_11__ {int stateBits; void* rgbGen; void* active; TYPE_1__* bundle; int /*<<< orphan*/  alphaGen; } ;
struct TYPE_10__ {int numLightmaps; int /*<<< orphan*/ ** lightmaps; int /*<<< orphan*/ * whiteImage; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** image; void* isLightmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGEN_SKIP ; 
 int /*<<< orphan*/  AGEN_VERTEX ; 
 void* CGEN_EXACT_VERTEX ; 
 void* CGEN_IDENTITY ; 
 void* CGEN_IDENTITY_LIGHTING ; 
 void* CGEN_LIGHTING_DIFFUSE ; 
 void* CGEN_VERTEX ; 
 int /*<<< orphan*/  FILE_HASH_SIZE ; 
 TYPE_2__* FinishShader () ; 
 void* GLS_DEFAULT ; 
 int GLS_DEPTHTEST_DISABLE ; 
 int GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ; 
 int GLS_DSTBLEND_ZERO ; 
 int GLS_SRCBLEND_DST_COLOR ; 
 int GLS_SRCBLEND_SRC_ALPHA ; 
 int /*<<< orphan*/  InitShader (char const*,int) ; 
 int LIGHTMAP_2D ; 
 int LIGHTMAP_BY_VERTEX ; 
 int LIGHTMAP_NONE ; 
 int LIGHTMAP_WHITEIMAGE ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char const*) ; 
 int generateHashValue (char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__** hashTable ; 
 void* qtrue ; 
 TYPE_5__ shader ; 
 TYPE_4__* stages ; 
 TYPE_3__ tr ; 

qhandle_t RE_RegisterShaderFromImage(const char *name, int lightmapIndex, image_t *image, qboolean mipRawImage) {
	int			hash;
	shader_t	*sh;

	hash = generateHashValue(name, FILE_HASH_SIZE);

	// probably not necessary since this function
	// only gets called from tr_font.c with lightmapIndex == LIGHTMAP_2D
	// but better safe than sorry.
	if ( lightmapIndex >= tr.numLightmaps ) {
		lightmapIndex = LIGHTMAP_WHITEIMAGE;
	}

	//
	// see if the shader is already loaded
	//
	for (sh=hashTable[hash]; sh; sh=sh->next) {
		// NOTE: if there was no shader or image available with the name strippedName
		// then a default shader is created with lightmapIndex == LIGHTMAP_NONE, so we
		// have to check all default shaders otherwise for every call to R_FindShader
		// with that same strippedName a new default shader is created.
		if ( (sh->lightmapIndex == lightmapIndex || sh->defaultShader) &&
			// index by name
			!Q_stricmp(sh->name, name)) {
			// match found
			return sh->index;
		}
	}

	InitShader( name, lightmapIndex );

	// FIXME: set these "need" values appropriately
	shader.needsNormal = qtrue;
	shader.needsST1 = qtrue;
	shader.needsST2 = qtrue;
	shader.needsColor = qtrue;

	//
	// create the default shading commands
	//
	if ( shader.lightmapIndex == LIGHTMAP_NONE ) {
		// dynamic colors at vertexes
		stages[0].bundle[0].image[0] = image;
		stages[0].active = qtrue;
		stages[0].rgbGen = CGEN_LIGHTING_DIFFUSE;
		stages[0].stateBits = GLS_DEFAULT;
	} else if ( shader.lightmapIndex == LIGHTMAP_BY_VERTEX ) {
		// explicit colors at vertexes
		stages[0].bundle[0].image[0] = image;
		stages[0].active = qtrue;
		stages[0].rgbGen = CGEN_EXACT_VERTEX;
		stages[0].alphaGen = AGEN_SKIP;
		stages[0].stateBits = GLS_DEFAULT;
	} else if ( shader.lightmapIndex == LIGHTMAP_2D ) {
		// GUI elements
		stages[0].bundle[0].image[0] = image;
		stages[0].active = qtrue;
		stages[0].rgbGen = CGEN_VERTEX;
		stages[0].alphaGen = AGEN_VERTEX;
		stages[0].stateBits = GLS_DEPTHTEST_DISABLE |
			  GLS_SRCBLEND_SRC_ALPHA |
			  GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA;
	} else if ( shader.lightmapIndex == LIGHTMAP_WHITEIMAGE ) {
		// fullbright level
		stages[0].bundle[0].image[0] = tr.whiteImage;
		stages[0].active = qtrue;
		stages[0].rgbGen = CGEN_IDENTITY_LIGHTING;
		stages[0].stateBits = GLS_DEFAULT;

		stages[1].bundle[0].image[0] = image;
		stages[1].active = qtrue;
		stages[1].rgbGen = CGEN_IDENTITY;
		stages[1].stateBits |= GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ZERO;
	} else {
		// two pass lightmap
		stages[0].bundle[0].image[0] = tr.lightmaps[shader.lightmapIndex];
		stages[0].bundle[0].isLightmap = qtrue;
		stages[0].active = qtrue;
		stages[0].rgbGen = CGEN_IDENTITY;	// lightmaps are scaled on creation
													// for identitylight
		stages[0].stateBits = GLS_DEFAULT;

		stages[1].bundle[0].image[0] = image;
		stages[1].active = qtrue;
		stages[1].rgbGen = CGEN_IDENTITY;
		stages[1].stateBits |= GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ZERO;
	}

	sh = FinishShader();
  return sh->index; 
}