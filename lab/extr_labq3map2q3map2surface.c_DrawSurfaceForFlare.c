#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_5__ {int entityNum; int lightStyle; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; void* shaderInfo; } ;
typedef  TYPE_1__ mapDrawSurface_t ;
struct TYPE_6__ {char* flareShader; } ;

/* Variables and functions */
 TYPE_1__* AllocDrawSurface (int /*<<< orphan*/ ) ; 
 int LS_NONE ; 
 int LS_NORMAL ; 
 int /*<<< orphan*/  SURFACE_FLARE ; 
 void* ShaderInfoForShader (char*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ emitFlares ; 
 TYPE_2__* game ; 
 scalar_t__ qfalse ; 

mapDrawSurface_t *DrawSurfaceForFlare( int entNum, vec3_t origin, vec3_t normal, vec3_t color, char *flareShader, int lightStyle ){
	mapDrawSurface_t    *ds;


	/* emit flares? */
	if ( emitFlares == qfalse ) {
		return NULL;
	}

	/* allocate drawsurface */
	ds = AllocDrawSurface( SURFACE_FLARE );
	ds->entityNum = entNum;

	/* set it up */
	if ( flareShader != NULL && flareShader[ 0 ] != '\0' ) {
		ds->shaderInfo = ShaderInfoForShader( flareShader );
	}
	else{
		ds->shaderInfo = ShaderInfoForShader( game->flareShader );
	}
	if ( origin != NULL ) {
		VectorCopy( origin, ds->lightmapOrigin );
	}
	if ( normal != NULL ) {
		VectorCopy( normal, ds->lightmapVecs[ 2 ] );
	}
	if ( color != NULL ) {
		VectorCopy( color, ds->lightmapVecs[ 0 ] );
	}

	/* store light style */
	ds->lightStyle = lightStyle;
	if ( ds->lightStyle < 0 || ds->lightStyle >= LS_NONE ) {
		ds->lightStyle = LS_NORMAL;
	}

	/* fixme: fog */

	/* return to sender */
	return ds;
}