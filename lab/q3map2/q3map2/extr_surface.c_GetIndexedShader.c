#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double shadeAngleDegrees; scalar_t__ tcGen; int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/ * vecs; void* nonplanar; void* forceMeta; void* globalTexture; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_8__ {char* shader; } ;
typedef  TYPE_2__ indexMap_t ;
typedef  int byte ;

/* Variables and functions */
 int MAX_QPATH ; 
 TYPE_1__* ShaderInfoForShader (char*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,...) ; 

shaderInfo_t *GetIndexedShader( shaderInfo_t *parent, indexMap_t *im, int numPoints, byte *shaderIndexes ){
	int i;
	byte minShaderIndex, maxShaderIndex;
	char shader[ MAX_QPATH ];
	shaderInfo_t    *si;


	/* early out if bad data */
	if ( im == NULL || numPoints <= 0 || shaderIndexes == NULL ) {
		return ShaderInfoForShader( "default" );
	}

	/* determine min/max index */
	minShaderIndex = 255;
	maxShaderIndex = 0;
	for ( i = 0; i < numPoints; i++ )
	{
		if ( shaderIndexes[ i ] < minShaderIndex ) {
			minShaderIndex = shaderIndexes[ i ];
		}
		if ( shaderIndexes[ i ] > maxShaderIndex ) {
			maxShaderIndex = shaderIndexes[ i ];
		}
	}

	/* set alpha inline */
	for ( i = 0; i < numPoints; i++ )
	{
		/* straight rip from terrain.c */
		if ( shaderIndexes[ i ] < maxShaderIndex ) {
			shaderIndexes[ i ] = 0;
		}
		else{
			shaderIndexes[ i ] = 255;
		}
	}

	/* make a shader name */
	if ( minShaderIndex == maxShaderIndex ) {
		sprintf( shader, "textures/%s_%d", im->shader, maxShaderIndex );
	}
	else{
		sprintf( shader, "textures/%s_%dto%d", im->shader, minShaderIndex, maxShaderIndex );
	}

	/* get the shader */
	si = ShaderInfoForShader( shader );

	/* inherit a few things from parent shader */
	if ( parent->globalTexture ) {
		si->globalTexture = qtrue;
	}
	if ( parent->forceMeta ) {
		si->forceMeta = qtrue;
	}
	if ( parent->nonplanar ) {
		si->nonplanar = qtrue;
	}
	if ( si->shadeAngleDegrees == 0.0 ) {
		si->shadeAngleDegrees = parent->shadeAngleDegrees;
	}
	if ( parent->tcGen && si->tcGen == qfalse ) {
		/* set xy texture projection */
		si->tcGen = qtrue;
		VectorCopy( parent->vecs[ 0 ], si->vecs[ 0 ] );
		VectorCopy( parent->vecs[ 1 ], si->vecs[ 1 ] );
	}
	if ( VectorLength( parent->lightmapAxis ) > 0.0f && VectorLength( si->lightmapAxis ) <= 0.0f ) {
		/* set lightmap projection axis */
		VectorCopy( parent->lightmapAxis, si->lightmapAxis );
	}

	/* return the shader */
	return si;
}