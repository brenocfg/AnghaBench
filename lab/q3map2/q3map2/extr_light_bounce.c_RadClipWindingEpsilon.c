#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {int numVerts; int* xyz; int** color; int* normal; int* st; int** lightmap; struct TYPE_10__* verts; } ;
typedef  TYPE_1__ radWinding_t ;
typedef  TYPE_1__ radVert_t ;
struct TYPE_11__ {int* dists; int* sides; } ;
typedef  TYPE_3__ clipWork_t ;

/* Variables and functions */
 int DotProduct (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_LIGHTMAPS ; 
 int MAX_POINTS_ON_WINDING ; 
 int SIDE_BACK ; 
 int SIDE_FRONT ; 
 int SIDE_ON ; 
 int /*<<< orphan*/  VectorNormalize (int*,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void RadClipWindingEpsilon( radWinding_t *in, vec3_t normal, vec_t dist,
								   vec_t epsilon, radWinding_t *front, radWinding_t *back, clipWork_t *cw ){
	vec_t           *dists;
	int             *sides;
	int counts[ 3 ];
	vec_t dot;                  /* ydnar: changed from static b/c of threading */ /* VC 4.2 optimizer bug if not static? */
	int i, j, k;
	radVert_t       *v1, *v2, mid;
	int maxPoints;


	/* crutch */
	dists = cw->dists;
	sides = cw->sides;

	/* clear counts */
	counts[ 0 ] = counts[ 1 ] = counts[ 2 ] = 0;

	/* determine sides for each point */
	for ( i = 0; i < in->numVerts; i++ )
	{
		dot = DotProduct( in->verts[ i ].xyz, normal );
		dot -= dist;
		dists[ i ] = dot;
		if ( dot > epsilon ) {
			sides[ i ] = SIDE_FRONT;
		}
		else if ( dot < -epsilon ) {
			sides[ i ] = SIDE_BACK;
		}
		else{
			sides[ i ] = SIDE_ON;
		}
		counts[ sides[ i ] ]++;
	}
	sides[ i ] = sides[ 0 ];
	dists[ i ] = dists[ 0 ];

	/* clear front and back */
	front->numVerts = back->numVerts = 0;

	/* handle all on one side cases */
	if ( counts[ 0 ] == 0 ) {
		memcpy( back, in, sizeof( radWinding_t ) );
		return;
	}
	if ( counts[ 1 ] == 0 ) {
		memcpy( front, in, sizeof( radWinding_t ) );
		return;
	}

	/* setup windings */
	maxPoints = in->numVerts + 4;

	/* do individual verts */
	for ( i = 0; i < in->numVerts; i++ )
	{
		/* do simple vertex copies first */
		v1 = &in->verts[ i ];

		if ( sides[ i ] == SIDE_ON ) {
			memcpy( &front->verts[ front->numVerts++ ], v1, sizeof( radVert_t ) );
			memcpy( &back->verts[ back->numVerts++ ], v1, sizeof( radVert_t ) );
			continue;
		}

		if ( sides[ i ] == SIDE_FRONT ) {
			memcpy( &front->verts[ front->numVerts++ ], v1, sizeof( radVert_t ) );
		}

		if ( sides[ i ] == SIDE_BACK ) {
			memcpy( &back->verts[ back->numVerts++ ], v1, sizeof( radVert_t ) );
		}

		if ( sides[ i + 1 ] == SIDE_ON || sides[ i + 1 ] == sides[ i ] ) {
			continue;
		}

		/* generate a split vertex */
		v2 = &in->verts[ ( i + 1 ) % in->numVerts ];

		dot = dists[ i ] / ( dists[ i ] - dists[ i + 1 ] );

		/* average vertex values */
		for ( j = 0; j < 4; j++ )
		{
			/* color */
			if ( j < 4 ) {
				for ( k = 0; k < MAX_LIGHTMAPS; k++ )
					mid.color[ k ][ j ] = v1->color[ k ][ j ] + dot * ( v2->color[ k ][ j ] - v1->color[ k ][ j ] );
			}

			/* xyz, normal */
			if ( j < 3 ) {
				mid.xyz[ j ] = v1->xyz[ j ] + dot * ( v2->xyz[ j ] - v1->xyz[ j ] );
				mid.normal[ j ] = v1->normal[ j ] + dot * ( v2->normal[ j ] - v1->normal[ j ] );
			}

			/* st, lightmap */
			if ( j < 2 ) {
				mid.st[ j ] = v1->st[ j ] + dot * ( v2->st[ j ] - v1->st[ j ] );
				for ( k = 0; k < MAX_LIGHTMAPS; k++ )
					mid.lightmap[ k ][ j ] = v1->lightmap[ k ][ j ] + dot * ( v2->lightmap[ k ][ j ] - v1->lightmap[ k ][ j ] );
			}
		}

		/* normalize the averaged normal */
		VectorNormalize( mid.normal, mid.normal );

		/* copy the midpoint to both windings */
		memcpy( &front->verts[ front->numVerts++ ], &mid, sizeof( radVert_t ) );
		memcpy( &back->verts[ back->numVerts++ ], &mid, sizeof( radVert_t ) );
	}

	/* error check */
	if ( front->numVerts > maxPoints ) {
		Error( "RadClipWindingEpsilon: points exceeded estimate" );
	}
	if ( front->numVerts > MAX_POINTS_ON_WINDING ) {
		Error( "RadClipWindingEpsilon: MAX_POINTS_ON_WINDING" );
	}
}