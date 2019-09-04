#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  mapDrawSurface_t ;
struct TYPE_12__ {float density; int inverseAlpha; float odds; } ;
typedef  TYPE_1__ foliage_t ;
struct TYPE_13__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ foliageInstance_t ;
struct TYPE_14__ {float* xyz; float* normal; scalar_t__** color; } ;
typedef  TYPE_3__ bspDrawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  LerpDrawVert (TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 size_t MAX_FOLIAGE_INSTANCES ; 
 int /*<<< orphan*/  PlaneFromPoints (float*,float*,float*,float*) ; 
 float Random () ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (TYPE_3__**,TYPE_3__**) ; 
 float VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 TYPE_2__* foliageInstances ; 
 size_t numFoliageInstances ; 

__attribute__((used)) static void SubdivideFoliageTriangle_r( mapDrawSurface_t *ds, foliage_t *foliage, bspDrawVert_t **tri ){
	bspDrawVert_t mid, *tri2[ 3 ];
	int max;


	/* limit test */
	if ( numFoliageInstances >= MAX_FOLIAGE_INSTANCES ) {
		return;
	}

	/* plane test */
	{
		vec4_t plane;


		/* make a plane */
		if ( !PlaneFromPoints( plane, tri[ 0 ]->xyz, tri[ 1 ]->xyz, tri[ 2 ]->xyz ) ) {
			return;
		}

		/* if normal is too far off vertical, then don't place an instance */
		if ( plane[ 2 ] < 0.5f ) {
			return;
		}
	}

	/* subdivide calc */
	{
		int i;
		float               *a, *b, dx, dy, dz, dist, maxDist;
		foliageInstance_t   *fi;


		/* get instance */
		fi = &foliageInstances[ numFoliageInstances ];

		/* find the longest edge and split it */
		max = -1;
		maxDist = 0.0f;
		VectorClear( fi->xyz );
		VectorClear( fi->normal );
		for ( i = 0; i < 3; i++ )
		{
			/* get verts */
			a = tri[ i ]->xyz;
			b = tri[ ( i + 1 ) % 3 ]->xyz;

			/* get dists */
			dx = a[ 0 ] - b[ 0 ];
			dy = a[ 1 ] - b[ 1 ];
			dz = a[ 2 ] - b[ 2 ];
			dist = ( dx * dx ) + ( dy * dy ) + ( dz * dz );

			/* longer? */
			if ( dist > maxDist ) {
				maxDist = dist;
				max = i;
			}

			/* add to centroid */
			VectorAdd( fi->xyz, tri[ i ]->xyz, fi->xyz );
			VectorAdd( fi->normal, tri[ i ]->normal, fi->normal );
		}

		/* is the triangle small enough? */
		if ( maxDist <= ( foliage->density * foliage->density ) ) {
			float alpha, odds, r;


			/* get average alpha */
			if ( foliage->inverseAlpha == 2 ) {
				alpha = 1.0f;
			}
			else
			{
				alpha = ( (float) tri[ 0 ]->color[ 0 ][ 3 ] + (float) tri[ 1 ]->color[ 0 ][ 3 ] + (float) tri[ 2 ]->color[ 0 ][ 3 ] ) / 765.0f;
				if ( foliage->inverseAlpha == 1 ) {
					alpha = 1.0f - alpha;
				}
				if ( alpha < 0.75f ) {
					return;
				}
			}

			/* roll the dice */
			odds = foliage->odds * alpha;
			r = Random();
			if ( r > odds ) {
				return;
			}

			/* scale centroid */
			VectorScale( fi->xyz, 0.33333333f, fi->xyz );
			if ( VectorNormalize( fi->normal, fi->normal ) == 0.0f ) {
				return;
			}

			/* add to count and return */
			numFoliageInstances++;
			return;
		}
	}

	/* split the longest edge and map it */
	LerpDrawVert( tri[ max ], tri[ ( max + 1 ) % 3 ], &mid );

	/* recurse to first triangle */
	VectorCopy( tri, tri2 );
	tri2[ max ] = &mid;
	SubdivideFoliageTriangle_r( ds, foliage, tri2 );

	/* recurse to second triangle */
	VectorCopy( tri, tri2 );
	tri2[ ( max + 1 ) % 3 ] = &mid;
	SubdivideFoliageTriangle_r( ds, foliage, tri2 );
}