#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int numpoints; float** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  float* vec4_t ;
struct TYPE_16__ {int numVerts; TYPE_4__* verts; int /*<<< orphan*/  lightmapScale; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shaderInfo; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  entityNum; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_17__ {float** planes; int numPlanes; float** texMat; int /*<<< orphan*/  si; } ;
typedef  TYPE_3__ decalProjector_t ;
struct TYPE_18__ {float* xyz; float* st; int** color; int /*<<< orphan*/  normal; } ;
typedef  TYPE_4__ bspDrawVert_t ;

/* Variables and functions */
 TYPE_2__* AllocDrawSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClipWindingEpsilon (TYPE_1__*,float*,float,float,TYPE_1__**,TYPE_1__**) ; 
 float DotProduct (float*,float*) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  PlaneFromPoints (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  SURFACE_DECAL ; 
 int /*<<< orphan*/  VectorAdd (float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  entityOrigin ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numDecalSurfaces ; 
 TYPE_4__* safe_malloc (int) ; 

__attribute__((used)) static void ProjectDecalOntoWinding( decalProjector_t *dp, mapDrawSurface_t *ds, winding_t *w ){
	int i, j;
	float d, d2, alpha;
	winding_t           *front, *back;
	mapDrawSurface_t    *ds2;
	bspDrawVert_t       *dv;
	vec4_t plane;


	/* dummy check */
	if ( w->numpoints < 3 ) {
		FreeWinding( w );
		return;
	}

	/* offset by entity origin */
	for ( i = 0; i < w->numpoints; i++ )
		VectorAdd( w->p[ i ], entityOrigin, w->p[ i ] );

	/* make a plane from the winding */
	if ( !PlaneFromPoints( plane, w->p[ 0 ], w->p[ 1 ], w->p[ 2 ] ) ) {
		FreeWinding( w );
		return;
	}

	/* backface check */
	d = DotProduct( dp->planes[ 0 ], plane );
	if ( d < -0.0001f ) {
		FreeWinding( w );
		return;
	}

	/* walk list of planes */
	for ( i = 0; i < dp->numPlanes; i++ )
	{
		/* chop winding by the plane */
		ClipWindingEpsilon( w, dp->planes[ i ], dp->planes[ i ][ 3 ], 0.0625f, &front, &back );
		FreeWinding( w );

		/* lose the front fragment */
		if ( front != NULL ) {
			FreeWinding( front );
		}

		/* if nothing left in back, then bail */
		if ( back == NULL ) {
			return;
		}

		/* reset winding */
		w = back;
	}

	/* nothing left? */
	if ( w == NULL || w->numpoints < 3 ) {
		return;
	}

	/* add to counts */
	numDecalSurfaces++;

	/* make a new surface */
	ds2 = AllocDrawSurface( SURFACE_DECAL );

	/* set it up */
	ds2->entityNum = ds->entityNum;
	ds2->castShadows = ds->castShadows;
	ds2->recvShadows = ds->recvShadows;
	ds2->shaderInfo = dp->si;
	ds2->fogNum = ds->fogNum;   /* why was this -1? */
	ds2->lightmapScale = ds->lightmapScale;
	ds2->numVerts = w->numpoints;
	ds2->verts = safe_malloc( ds2->numVerts * sizeof( *ds2->verts ) );
	memset( ds2->verts, 0, ds2->numVerts * sizeof( *ds2->verts ) );

	/* set vertexes */
	for ( i = 0; i < ds2->numVerts; i++ )
	{
		/* get vertex */
		dv = &ds2->verts[ i ];

		/* set alpha */
		d = DotProduct( w->p[ i ], dp->planes[ 0 ] ) - dp->planes[ 0 ][ 3 ];
		d2 = DotProduct( w->p[ i ], dp->planes[ 1 ] ) - dp->planes[ 1 ][ 3 ];
		alpha = 255.0f * d2 / ( d + d2 );
		if ( alpha > 255 ) {
			alpha = 255;
		}
		else if ( alpha < 0 ) {
			alpha = 0;
		}

		/* set misc */
		VectorSubtract( w->p[ i ], entityOrigin, dv->xyz );
		VectorCopy( plane, dv->normal );
		dv->st[ 0 ] = DotProduct( dv->xyz, dp->texMat[ 0 ] ) + dp->texMat[ 0 ][ 3 ];
		dv->st[ 1 ] = DotProduct( dv->xyz, dp->texMat[ 1 ] ) + dp->texMat[ 1 ][ 3 ];

		/* set color */
		for ( j = 0; j < MAX_LIGHTMAPS; j++ )
		{
			dv->color[ j ][ 0 ] = 255;
			dv->color[ j ][ 1 ] = 255;
			dv->color[ j ][ 2 ] = 255;
			dv->color[ j ][ 3 ] = alpha;
		}
	}
}