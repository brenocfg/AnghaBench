#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_16__ {scalar_t__ entityNum; scalar_t__ castShadows; scalar_t__ recvShadows; scalar_t__ fogNum; int sampleSize; float* plane; size_t planeNum; scalar_t__ surfaceNum; float* lightmapAxis; size_t* indexes; int /*<<< orphan*/  side; TYPE_2__* si; } ;
typedef  TYPE_3__ metaTriangle_t ;
struct TYPE_17__ {int numIndexes; scalar_t__ entityNum; scalar_t__ castShadows; scalar_t__ recvShadows; scalar_t__ fogNum; int sampleSize; size_t planeNum; scalar_t__ surfaceNum; float* lightmapAxis; float* mins; float* maxs; int* texRange; int* indexes; int /*<<< orphan*/  sideRef; int /*<<< orphan*/  numVerts; TYPE_1__* verts; TYPE_2__* shaderInfo; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
struct TYPE_19__ {float* normal; scalar_t__ dist; } ;
struct TYPE_18__ {int /*<<< orphan*/  xyz; } ;
struct TYPE_15__ {scalar_t__ nonplanar; int compileFlags; int lmCustomWidth; } ;
struct TYPE_14__ {int /*<<< orphan*/ * xyz; } ;

/* Variables and functions */
 int AXIS_SCORE ; 
 int AddMetaVertToSurface (TYPE_4__*,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  AllocSideRef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int C_VERTEXLIT ; 
 scalar_t__ CalcSurfaceTextureRange (TYPE_4__*) ; 
 int DotProduct (float*,scalar_t__*) ; 
 scalar_t__ ST_SCORE ; 
 scalar_t__ ST_SCORE2 ; 
 int SURFACE_SCORE ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Printf (char*,int /*<<< orphan*/ ) ; 
 int UNSUITABLE_TRIANGLE ; 
 int VERT_SCORE ; 
 scalar_t__ VectorCompare (float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (float*) ; 
 TYPE_8__* mapplanes ; 
 int maxSurfaceIndexes ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 TYPE_5__* metaVerts ; 
 float npDegrees ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

__attribute__((used)) static int AddMetaTriangleToSurface( mapDrawSurface_t *ds, metaTriangle_t *tri, qboolean testAdd ){
	int i, score, coincident, ai, bi, ci, oldTexRange[ 2 ];
	float lmMax;
	vec3_t mins, maxs;
	qboolean inTexRange, es, et;
	mapDrawSurface_t old;


	/* overflow check */
	if ( ds->numIndexes >= maxSurfaceIndexes ) {
		return 0;
	}

	/* test the triangle */
	if ( ds->entityNum != tri->entityNum ) { /* ydnar: added 2002-07-06 */
		return 0;
	}
	if ( ds->castShadows != tri->castShadows || ds->recvShadows != tri->recvShadows ) {
		return 0;
	}
	if ( ds->shaderInfo != tri->si || ds->fogNum != tri->fogNum || ds->sampleSize != tri->sampleSize ) {
		return 0;
	}
	#if 0
	if ( !( ds->shaderInfo->compileFlags & C_VERTEXLIT ) &&
	     //% VectorCompare( ds->lightmapAxis, tri->lightmapAxis ) == qfalse )
		 DotProduct( ds->lightmapAxis, tri->plane ) < 0.25f ) {
		return 0;
	}
	#endif

	/* planar surfaces will only merge with triangles in the same plane */
	if ( npDegrees == 0.0f && ds->shaderInfo->nonplanar == qfalse && ds->planeNum >= 0 ) {
		if ( VectorCompare( mapplanes[ ds->planeNum ].normal, tri->plane ) == qfalse || mapplanes[ ds->planeNum ].dist != tri->plane[ 3 ] ) {
			return 0;
		}
		if ( tri->planeNum >= 0 && tri->planeNum != ds->planeNum ) {
			return 0;
		}
	}

	/* set initial score */
	score = tri->surfaceNum == ds->surfaceNum ? SURFACE_SCORE : 0;

	/* score the the dot product of lightmap axis to plane */
	if ( ( ds->shaderInfo->compileFlags & C_VERTEXLIT ) || VectorCompare( ds->lightmapAxis, tri->lightmapAxis ) ) {
		score += AXIS_SCORE;
	}
	else{
		score += AXIS_SCORE * DotProduct( ds->lightmapAxis, tri->plane );
	}

	/* preserve old drawsurface if this fails */
	memcpy( &old, ds, sizeof( *ds ) );

	/* attempt to add the verts */
	coincident = 0;
	ai = AddMetaVertToSurface( ds, &metaVerts[ tri->indexes[ 0 ] ], &coincident );
	bi = AddMetaVertToSurface( ds, &metaVerts[ tri->indexes[ 1 ] ], &coincident );
	ci = AddMetaVertToSurface( ds, &metaVerts[ tri->indexes[ 2 ] ], &coincident );

	/* check vertex underflow */
	if ( ai < 0 || bi < 0 || ci < 0 ) {
		memcpy( ds, &old, sizeof( *ds ) );
		return 0;
	}

	/* score coincident vertex count (2003-02-14: changed so this only matters on planar surfaces) */
	score += ( coincident * VERT_SCORE );

	/* add new vertex bounds to mins/maxs */
	VectorCopy( ds->mins, mins );
	VectorCopy( ds->maxs, maxs );
	AddPointToBounds( metaVerts[ tri->indexes[ 0 ] ].xyz, mins, maxs );
	AddPointToBounds( metaVerts[ tri->indexes[ 1 ] ].xyz, mins, maxs );
	AddPointToBounds( metaVerts[ tri->indexes[ 2 ] ].xyz, mins, maxs );

	/* check lightmap bounds overflow (after at least 1 triangle has been added) */
	if ( !( ds->shaderInfo->compileFlags & C_VERTEXLIT ) &&
		 ds->numIndexes > 0 && VectorLength( ds->lightmapAxis ) > 0.0f &&
		 ( VectorCompare( ds->mins, mins ) == qfalse || VectorCompare( ds->maxs, maxs ) == qfalse ) ) {
		/* set maximum size before lightmap scaling (normally 2032 units) */
		/* 2004-02-24: scale lightmap test size by 2 to catch larger brush faces */
		/* 2004-04-11: reverting to actual lightmap size */
		lmMax = ( ds->sampleSize * ( ds->shaderInfo->lmCustomWidth - 1 ) );
		for ( i = 0; i < 3; i++ )
		{
			if ( ( maxs[ i ] - mins[ i ] ) > lmMax ) {
				memcpy( ds, &old, sizeof( *ds ) );
				return 0;
			}
		}
	}

	/* check texture range overflow */
	oldTexRange[ 0 ] = ds->texRange[ 0 ];
	oldTexRange[ 1 ] = ds->texRange[ 1 ];
	inTexRange = CalcSurfaceTextureRange( ds );

	es = ( ds->texRange[ 0 ] > oldTexRange[ 0 ] ) ? qtrue : qfalse;
	et = ( ds->texRange[ 1 ] > oldTexRange[ 1 ] ) ? qtrue : qfalse;

	if ( inTexRange == qfalse && ds->numIndexes > 0 ) {
		memcpy( ds, &old, sizeof( *ds ) );
		return UNSUITABLE_TRIANGLE;
	}

	/* score texture range */
	if ( ds->texRange[ 0 ] <= oldTexRange[ 0 ] ) {
		score += ST_SCORE2;
	}
	else if ( ds->texRange[ 0 ] > oldTexRange[ 0 ] && oldTexRange[ 1 ] > oldTexRange[ 0 ] ) {
		score += ST_SCORE;
	}

	if ( ds->texRange[ 1 ] <= oldTexRange[ 1 ] ) {
		score += ST_SCORE2;
	}
	else if ( ds->texRange[ 1 ] > oldTexRange[ 1 ] && oldTexRange[ 0 ] > oldTexRange[ 1 ] ) {
		score += ST_SCORE;
	}


	/* go through the indexes and try to find an existing triangle that matches abc */
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		/* 2002-03-11 (birthday!): rotate the triangle 3x to find an existing triangle */
		if ( ( ai == ds->indexes[ i ] && bi == ds->indexes[ i + 1 ] && ci == ds->indexes[ i + 2 ] ) ||
			 ( bi == ds->indexes[ i ] && ci == ds->indexes[ i + 1 ] && ai == ds->indexes[ i + 2 ] ) ||
			 ( ci == ds->indexes[ i ] && ai == ds->indexes[ i + 1 ] && bi == ds->indexes[ i + 2 ] ) ) {
			/* triangle already present */
			memcpy( ds, &old, sizeof( *ds ) );
			tri->si = NULL;
			return 0;
		}

		/* rotate the triangle 3x to find an inverse triangle (error case) */
		if ( ( ai == ds->indexes[ i ] && bi == ds->indexes[ i + 2 ] && ci == ds->indexes[ i + 1 ] ) ||
			 ( bi == ds->indexes[ i ] && ci == ds->indexes[ i + 2 ] && ai == ds->indexes[ i + 1 ] ) ||
			 ( ci == ds->indexes[ i ] && ai == ds->indexes[ i + 2 ] && bi == ds->indexes[ i + 1 ] ) ) {
			/* warn about it */
			Sys_FPrintf( SYS_WRN, "WARNING: Flipped triangle: (%6.0f %6.0f %6.0f) (%6.0f %6.0f %6.0f) (%6.0f %6.0f %6.0f)\n",
						ds->verts[ ai ].xyz[ 0 ], ds->verts[ ai ].xyz[ 1 ], ds->verts[ ai ].xyz[ 2 ],
						ds->verts[ bi ].xyz[ 0 ], ds->verts[ bi ].xyz[ 1 ], ds->verts[ bi ].xyz[ 2 ],
						ds->verts[ ci ].xyz[ 0 ], ds->verts[ ci ].xyz[ 1 ], ds->verts[ ci ].xyz[ 2 ] );

			/* reverse triangle already present */
			memcpy( ds, &old, sizeof( *ds ) );
			tri->si = NULL;
			return 0;
		}
	}

	/* add the triangle indexes */
	if ( ds->numIndexes < maxSurfaceIndexes ) {
		ds->indexes[ ds->numIndexes++ ] = ai;
	}
	if ( ds->numIndexes < maxSurfaceIndexes ) {
		ds->indexes[ ds->numIndexes++ ] = bi;
	}
	if ( ds->numIndexes < maxSurfaceIndexes ) {
		ds->indexes[ ds->numIndexes++ ] = ci;
	}

	/* check index overflow */
	if ( ds->numIndexes >= maxSurfaceIndexes  ) {
		memcpy( ds, &old, sizeof( *ds ) );
		return 0;
	}

	/* sanity check the indexes */
	if ( ds->numIndexes >= 3 &&
		 ( ds->indexes[ ds->numIndexes - 3 ] == ds->indexes[ ds->numIndexes - 2 ] ||
		   ds->indexes[ ds->numIndexes - 3 ] == ds->indexes[ ds->numIndexes - 1 ] ||
		   ds->indexes[ ds->numIndexes - 2 ] == ds->indexes[ ds->numIndexes - 1 ] ) ) {
		Sys_Printf( "DEG:%d! ", ds->numVerts );
	}

	/* testing only? */
	if ( testAdd ) {
		memcpy( ds, &old, sizeof( *ds ) );
	}
	else
	{
		/* copy bounds back to surface */
		VectorCopy( mins, ds->mins );
		VectorCopy( maxs, ds->maxs );

		/* mark triangle as used */
		tri->si = NULL;
	}

	/* add a side reference */
	ds->sideRef = AllocSideRef( tri->side, ds->sideRef );

	/* return to sender */
	return score;
}