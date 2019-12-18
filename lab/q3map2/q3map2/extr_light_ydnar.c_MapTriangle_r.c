#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  surfaceInfo_t ;
typedef  int /*<<< orphan*/  rawLightmap_t ;
struct TYPE_9__ {float** lightmap; } ;
typedef  TYPE_1__ bspDrawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  LerpDrawVert (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MapSingleLuxel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (TYPE_1__**,TYPE_1__**) ; 
 float subdivideThreshold ; 

__attribute__((used)) static void MapTriangle_r( rawLightmap_t *lm, surfaceInfo_t *info, bspDrawVert_t *dv[ 3 ], vec4_t plane, vec3_t stv[ 3 ], vec3_t ttv[ 3 ] ){
	bspDrawVert_t mid, *dv2[ 3 ];
	int max;


	/* map the vertexes */
	#if 0
	MapSingleLuxel( lm, info, dv[ 0 ], plane, 1, stv, ttv );
	MapSingleLuxel( lm, info, dv[ 1 ], plane, 1, stv, ttv );
	MapSingleLuxel( lm, info, dv[ 2 ], plane, 1, stv, ttv );
	#endif

	/* subdivide calc */
	{
		int i;
		float       *a, *b, dx, dy, dist, maxDist;


		/* find the longest edge and split it */
		max = -1;
		maxDist = 0;
		for ( i = 0; i < 3; i++ )
		{
			/* get verts */
			a = dv[ i ]->lightmap[ 0 ];
			b = dv[ ( i + 1 ) % 3 ]->lightmap[ 0 ];

			/* get dists */
			dx = a[ 0 ] - b[ 0 ];
			dy = a[ 1 ] - b[ 1 ];
			dist = ( dx * dx ) + ( dy * dy );   //% sqrt( (dx * dx) + (dy * dy) );

			/* longer? */
			if ( dist > maxDist ) {
				maxDist = dist;
				max = i;
			}
		}

		/* try to early out */
		if ( max < 0 || maxDist <= subdivideThreshold ) { /* ydnar: was i < 0 instead of max < 0 (?) */
			return;
		}
	}

	/* split the longest edge and map it */
	LerpDrawVert( dv[ max ], dv[ ( max + 1 ) % 3 ], &mid );
	MapSingleLuxel( lm, info, &mid, plane, 1, stv, ttv );

	/* push the point up a little bit to account for fp creep (fixme: revisit this) */
	//%	VectorMA( mid.xyz, 2.0f, mid.normal, mid.xyz );

	/* recurse to first triangle */
	VectorCopy( dv, dv2 );
	dv2[ max ] = &mid;
	MapTriangle_r( lm, info, dv2, plane, stv, ttv );

	/* recurse to second triangle */
	VectorCopy( dv, dv2 );
	dv2[ ( max + 1 ) % 3 ] = &mid;
	MapTriangle_r( lm, info, dv2, plane, stv, ttv );
}