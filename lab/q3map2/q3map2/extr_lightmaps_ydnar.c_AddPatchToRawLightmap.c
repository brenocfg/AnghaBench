#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widthTable ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_16__ {int /*<<< orphan*/  patchIterations; } ;
typedef  TYPE_1__ surfaceInfo_t ;
struct TYPE_17__ {int w; float sampleSize; int customWidth; int h; int customHeight; void** wrap; void* finished; } ;
typedef  TYPE_2__ rawLightmap_t ;
typedef  void* qboolean ;
struct TYPE_18__ {int width; int height; TYPE_4__* verts; } ;
typedef  TYPE_3__ mesh_t ;
typedef  int /*<<< orphan*/  heightTable ;
struct TYPE_19__ {float** lightmap; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_4__ bspDrawVert_t ;
struct TYPE_20__ {int patchWidth; int patchHeight; size_t firstVert; } ;
typedef  TYPE_5__ bspDrawSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMesh (TYPE_3__*) ; 
 int MAX_EXPANDED_AXIS ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_3__) ; 
 TYPE_3__* RemoveLinearMeshColumnsRows (TYPE_3__*) ; 
 TYPE_3__* SubdivideMesh2 (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* bspDrawSurfaces ; 
 void* ceil (float) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numPatchesLightmapped ; 
 void* qfalse ; 
 void* qtrue ; 
 float superSample ; 
 TYPE_1__* surfaceInfos ; 
 TYPE_4__* yDrawVerts ; 

qboolean AddPatchToRawLightmap( int num, rawLightmap_t *lm ){
	bspDrawSurface_t    *ds;
	surfaceInfo_t       *info;
	int x, y;
	bspDrawVert_t       *verts, *a, *b;
	vec3_t delta;
	mesh_t src, *subdivided, *mesh;
	float sBasis, tBasis, s, t;
	float length, widthTable[ MAX_EXPANDED_AXIS ], heightTable[ MAX_EXPANDED_AXIS ];


	/* patches finish a raw lightmap */
	lm->finished = qtrue;

	/* get surface and info  */
	ds = &bspDrawSurfaces[ num ];
	info = &surfaceInfos[ num ];

	/* make a temporary mesh from the drawsurf */
	src.width = ds->patchWidth;
	src.height = ds->patchHeight;
	src.verts = &yDrawVerts[ ds->firstVert ];
	//%	subdivided = SubdivideMesh( src, 8, 512 );
	subdivided = SubdivideMesh2( src, info->patchIterations );

	/* fit it to the curve and remove colinear verts on rows/columns */
	PutMeshOnCurve( *subdivided );
	mesh = RemoveLinearMeshColumnsRows( subdivided );
	FreeMesh( subdivided );

	/* find the longest distance on each row/column */
	verts = mesh->verts;
	memset( widthTable, 0, sizeof( widthTable ) );
	memset( heightTable, 0, sizeof( heightTable ) );
	for ( y = 0; y < mesh->height; y++ )
	{
		for ( x = 0; x < mesh->width; x++ )
		{
			/* get width */
			if ( x + 1 < mesh->width ) {
				a = &verts[ ( y * mesh->width ) + x ];
				b = &verts[ ( y * mesh->width ) + x + 1 ];
				VectorSubtract( a->xyz, b->xyz, delta );
				length = VectorLength( delta );
				if ( length > widthTable[ x ] ) {
					widthTable[ x ] = length;
				}
			}

			/* get height */
			if ( y + 1 < mesh->height ) {
				a = &verts[ ( y * mesh->width ) + x ];
				b = &verts[ ( ( y + 1 ) * mesh->width ) + x ];
				VectorSubtract( a->xyz, b->xyz, delta );
				length = VectorLength( delta );
				if ( length > heightTable[ y ] ) {
					heightTable[ y ] = length;
				}
			}
		}
	}

	/* determine lightmap width */
	length = 0;
	for ( x = 0; x < ( mesh->width - 1 ); x++ )
		length += widthTable[ x ];
	lm->w = lm->sampleSize != 0 ? ceil( length / lm->sampleSize ) + 1 : 0;
	if ( lm->w < ds->patchWidth ) {
		lm->w = ds->patchWidth;
	}
	if ( lm->w > lm->customWidth ) {
		lm->w = lm->customWidth;
	}
	sBasis = (float) ( lm->w - 1 ) / (float) ( ds->patchWidth - 1 );

	/* determine lightmap height */
	length = 0;
	for ( y = 0; y < ( mesh->height - 1 ); y++ )
		length += heightTable[ y ];
	lm->h = lm->sampleSize != 0 ? ceil( length / lm->sampleSize ) + 1 : 0;
	if ( lm->h < ds->patchHeight ) {
		lm->h = ds->patchHeight;
	}
	if ( lm->h > lm->customHeight ) {
		lm->h = lm->customHeight;
	}
	tBasis = (float) ( lm->h - 1 ) / (float) ( ds->patchHeight - 1 );

	/* free the temporary mesh */
	FreeMesh( mesh );

	/* set the lightmap texture coordinates in yDrawVerts */
	lm->wrap[ 0 ] = qtrue;
	lm->wrap[ 1 ] = qtrue;
	verts = &yDrawVerts[ ds->firstVert ];
	for ( y = 0; y < ds->patchHeight; y++ )
	{
		t = ( tBasis * y ) + 0.5f;
		for ( x = 0; x < ds->patchWidth; x++ )
		{
			s = ( sBasis * x ) + 0.5f;
			verts[ ( y * ds->patchWidth ) + x ].lightmap[ 0 ][ 0 ] = s * superSample;
			verts[ ( y * ds->patchWidth ) + x ].lightmap[ 0 ][ 1 ] = t * superSample;

			if ( y == 0 && !VectorCompare( verts[ x ].xyz, verts[ ( ( ds->patchHeight - 1 ) * ds->patchWidth ) + x ].xyz ) ) {
				lm->wrap[ 1 ] = qfalse;
			}
		}

		if ( !VectorCompare( verts[ ( y * ds->patchWidth ) ].xyz, verts[ ( y * ds->patchWidth ) + ( ds->patchWidth - 1 ) ].xyz ) ) {
			lm->wrap[ 0 ] = qfalse;
		}
	}

	/* debug code: */
	//%	Sys_Printf( "wrap S: %d wrap T: %d\n", lm->wrap[ 0 ], lm->wrap[ 1 ] );
	//% if( lm->w > (ds->lightmapWidth & 0xFF) || lm->h > (ds->lightmapHeight & 0xFF) )
	//%		Sys_Printf( "Patch lightmap: (%3d %3d) > (%3d, %3d)\n", lm->w, lm->h, ds->lightmapWidth & 0xFF, ds->lightmapHeight & 0xFF );
	//% ds->lightmapWidth = lm->w | (ds->lightmapWidth & 0xFFFF0000);
	//% ds->lightmapHeight = lm->h | (ds->lightmapHeight & 0xFFFF0000);

	/* add to counts */
	numPatchesLightmapped++;

	/* return */
	return qtrue;
}