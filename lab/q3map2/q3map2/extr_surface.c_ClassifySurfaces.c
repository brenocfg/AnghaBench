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
typedef  float* vec4_t ;
typedef  float* vec3_t ;
struct TYPE_7__ {int compileFlags; float* lightmapAxis; int lightmapSampleSize; } ;
typedef  TYPE_2__ shaderInfo_t ;
struct TYPE_8__ {scalar_t__ type; int numVerts; size_t planeNum; float** lightmapVecs; float* lightmapAxis; int sampleSize; int lightmapScale; TYPE_2__* shaderInfo; TYPE_1__* verts; void* planar; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_9__ {float* normal; float dist; } ;
struct TYPE_6__ {float* xyz; float* normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int C_VERTEXLIT ; 
 int /*<<< orphan*/  CalcLightmapAxis (float*,float*) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (float*,float*) ; 
 int FindFloatPlane (float*,float,int,float**) ; 
 scalar_t__ PLANAR_EPSILON ; 
 int SHADER_MAX_VERTEXES ; 
 scalar_t__ SURFACE_BAD ; 
 scalar_t__ SURFACE_FACE ; 
 scalar_t__ SURFACE_FORCED_META ; 
 scalar_t__ SURFACE_PATCH ; 
 scalar_t__ SURFACE_TRIANGLES ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (float*) ; 
 scalar_t__ fabs (float) ; 
 TYPE_4__* mapplanes ; 
 void* qfalse ; 
 void* qtrue ; 
 int sampleSize ; 

void ClassifySurfaces( int numSurfs, mapDrawSurface_t *ds ){
	int i, bestAxis;
	float dist;
	vec4_t plane;
	shaderInfo_t        *si;
	static vec3_t axii[ 6 ] =
	{
		{ 0, 0, -1 },
		{ 0, 0, 1 },
		{ -1, 0, 0 },
		{ 1, 0, 0 },
		{ 0, -1, 0 },
		{ 0, 1, 0 }
	};


	/* walk the list of surfaces */
	for ( ; numSurfs > 0; numSurfs--, ds++ )
	{
		/* ignore bogus (or flare) surfaces */
		if ( ds->type == SURFACE_BAD || ds->numVerts <= 0 ) {
			continue;
		}

		/* get shader */
		si = ds->shaderInfo;

		/* -----------------------------------------------------------------
		   force meta if vertex count is too high or shader requires it
		   ----------------------------------------------------------------- */

		if ( ds->type != SURFACE_PATCH && ds->type != SURFACE_FACE ) {
			if ( ds->numVerts > SHADER_MAX_VERTEXES ) {
				ds->type = SURFACE_FORCED_META;
			}
		}

		/* -----------------------------------------------------------------
		   plane and bounding box classification
		   ----------------------------------------------------------------- */

		/* set surface bounding box */
		ClearBounds( ds->mins, ds->maxs );
		for ( i = 0; i < ds->numVerts; i++ )
			AddPointToBounds( ds->verts[ i ].xyz, ds->mins, ds->maxs );

		/* try to get an existing plane */
		if ( ds->planeNum >= 0 ) {
			VectorCopy( mapplanes[ ds->planeNum ].normal, plane );
			plane[ 3 ] = mapplanes[ ds->planeNum ].dist;
		}

		/* construct one from the first vert with a valid normal */
		else
		{
			VectorClear( plane );
			plane[ 3 ] = 0.0f;
			for ( i = 0; i < ds->numVerts; i++ )
			{
				if ( ds->verts[ i ].normal[ 0 ] != 0.0f && ds->verts[ i ].normal[ 1 ] != 0.0f && ds->verts[ i ].normal[ 2 ] != 0.0f ) {
					VectorCopy( ds->verts[ i ].normal, plane );
					plane[ 3 ] = DotProduct( ds->verts[ i ].xyz, plane );
					break;
				}
			}
		}

		/* test for bogus plane */
		if ( VectorLength( plane ) <= 0.0f ) {
			ds->planar = qfalse;
			ds->planeNum = -1;
		}
		else
		{
			/* determine if surface is planar */
			ds->planar = qtrue;

			/* test each vert */
			for ( i = 0; i < ds->numVerts; i++ )
			{
				/* point-plane test */
				dist = DotProduct( ds->verts[ i ].xyz, plane ) - plane[ 3 ];
				if ( fabs( dist ) > PLANAR_EPSILON ) {
					//%	if( ds->planeNum >= 0 )
					//%	{
					//%		Sys_FPrintf( SYS_WRN, "WARNING: Planar surface marked unplanar (%f > %f)\n", fabs( dist ), PLANAR_EPSILON );
					//%		ds->verts[ i ].color[ 0 ][ 0 ] = ds->verts[ i ].color[ 0 ][ 2 ] = 0;
					//%	}
					ds->planar = qfalse;
					break;
				}
			}
		}

		/* find map plane if necessary */
		if ( ds->planar ) {
			if ( ds->planeNum < 0 ) {
				ds->planeNum = FindFloatPlane( plane, plane[ 3 ], 1, &ds->verts[ 0 ].xyz );
			}
			VectorCopy( plane, ds->lightmapVecs[ 2 ] );
		}
		else
		{
			ds->planeNum = -1;
			VectorClear( ds->lightmapVecs[ 2 ] );
			//% if( ds->type == SURF_META || ds->type == SURF_FACE )
			//%		Sys_FPrintf( SYS_WRN, "WARNING: Non-planar face (%d): %s\n", ds->planeNum, ds->shaderInfo->shader );
		}

		/* -----------------------------------------------------------------
		   lightmap bounds and axis projection
		   ----------------------------------------------------------------- */

		/* vertex lit surfaces don't need this information */
		if ( si->compileFlags & C_VERTEXLIT || ds->type == SURFACE_TRIANGLES ) {
			VectorClear( ds->lightmapAxis );
			//%	VectorClear( ds->lightmapVecs[ 2 ] );
			ds->sampleSize = 0;
			continue;
		}

		/* the shader can specify an explicit lightmap axis */
		if ( si->lightmapAxis[ 0 ] || si->lightmapAxis[ 1 ] || si->lightmapAxis[ 2 ] ) {
			VectorCopy( si->lightmapAxis, ds->lightmapAxis );
		}
		else if ( ds->type == SURFACE_FORCED_META ) {
			VectorClear( ds->lightmapAxis );
		}
		else if ( ds->planar ) {
			CalcLightmapAxis( plane, ds->lightmapAxis );
		}
		else
		{
			/* find best lightmap axis */
			for ( bestAxis = 0; bestAxis < 6; bestAxis++ )
			{
				for ( i = 0; i < ds->numVerts && bestAxis < 6; i++ )
				{
					//% Sys_Printf( "Comparing %1.3f %1.3f %1.3f to %1.3f %1.3f %1.3f\n",
					//%     ds->verts[ i ].normal[ 0 ], ds->verts[ i ].normal[ 1 ], ds->verts[ i ].normal[ 2 ],
					//%     axii[ bestAxis ][ 0 ], axii[ bestAxis ][ 1 ], axii[ bestAxis ][ 2 ] );
					if ( DotProduct( ds->verts[ i ].normal, axii[ bestAxis ] ) < 0.25f ) { /* fixme: adjust this tolerance to taste */
						break;
					}
				}

				if ( i == ds->numVerts ) {
					break;
				}
			}

			/* set axis if possible */
			if ( bestAxis < 6 ) {
				//% if( ds->type == SURFACE_PATCH )
				//%     Sys_Printf( "Mapped axis %d onto patch\n", bestAxis );
				VectorCopy( axii[ bestAxis ], ds->lightmapAxis );
			}

			/* debug code */
			//% if( ds->type == SURFACE_PATCH )
			//%     Sys_Printf( "Failed to map axis %d onto patch\n", bestAxis );
		}

		/* get lightmap sample size */
		if ( ds->sampleSize <= 0 ) {
			ds->sampleSize = sampleSize;
			if ( ds->shaderInfo->lightmapSampleSize ) {
				ds->sampleSize = ds->shaderInfo->lightmapSampleSize;
			}
			if ( ds->lightmapScale > 0 ) {
				ds->sampleSize *= ds->lightmapScale;
			}
			if ( ds->sampleSize <= 0 ) {
				ds->sampleSize = 1;
			}
			else if ( ds->sampleSize > 16384 ) { /* powers of 2 are preferred */
				ds->sampleSize = 16384;
			}
		}
	}
}