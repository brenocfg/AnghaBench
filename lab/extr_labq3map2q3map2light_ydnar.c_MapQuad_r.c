#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  surfaceInfo_t ;
typedef  int /*<<< orphan*/  rawLightmap_t ;
struct TYPE_7__ {float** lightmap; } ;
typedef  TYPE_1__ bspDrawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  LerpDrawVert (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MapSingleLuxel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float subdivideThreshold ; 

__attribute__((used)) static void MapQuad_r( rawLightmap_t *lm, surfaceInfo_t *info, bspDrawVert_t *dv[ 4 ], vec4_t plane, vec3_t stv[ 4 ], vec3_t ttv[ 4 ] ){
	bspDrawVert_t mid[ 2 ], *dv2[ 4 ];
	int max;


	/* subdivide calc */
	{
		int i;
		float       *a, *b, dx, dy, dist, maxDist;


		/* find the longest edge and split it */
		max = -1;
		maxDist = 0;
		for ( i = 0; i < 4; i++ )
		{
			/* get verts */
			a = dv[ i ]->lightmap[ 0 ];
			b = dv[ ( i + 1 ) % 4 ]->lightmap[ 0 ];

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
		if ( max < 0 || maxDist <= subdivideThreshold ) {
			return;
		}
	}

	/* we only care about even/odd edges */
	max &= 1;

	/* split the longest edges */
	LerpDrawVert( dv[ max ], dv[ ( max + 1 ) % 4 ], &mid[ 0 ] );
	LerpDrawVert( dv[ max + 2 ], dv[ ( max + 3 ) % 4 ], &mid[ 1 ] );

	/* map the vertexes */
	MapSingleLuxel( lm, info, &mid[ 0 ], plane, 1, stv, ttv );
	MapSingleLuxel( lm, info, &mid[ 1 ], plane, 1, stv, ttv );

	/* 0 and 2 */
	if ( max == 0 ) {
		/* recurse to first quad */
		dv2[ 0 ] = dv[ 0 ];
		dv2[ 1 ] = &mid[ 0 ];
		dv2[ 2 ] = &mid[ 1 ];
		dv2[ 3 ] = dv[ 3 ];
		MapQuad_r( lm, info, dv2, plane, stv, ttv );

		/* recurse to second quad */
		dv2[ 0 ] = &mid[ 0 ];
		dv2[ 1 ] = dv[ 1 ];
		dv2[ 2 ] = dv[ 2 ];
		dv2[ 3 ] = &mid[ 1 ];
		MapQuad_r( lm, info, dv2, plane, stv, ttv );
	}

	/* 1 and 3 */
	else
	{
		/* recurse to first quad */
		dv2[ 0 ] = dv[ 0 ];
		dv2[ 1 ] = dv[ 1 ];
		dv2[ 2 ] = &mid[ 0 ];
		dv2[ 3 ] = &mid[ 1 ];
		MapQuad_r( lm, info, dv2, plane, stv, ttv );

		/* recurse to second quad */
		dv2[ 0 ] = &mid[ 1 ];
		dv2[ 1 ] = &mid[ 0 ];
		dv2[ 2 ] = dv[ 2 ];
		dv2[ 3 ] = dv[ 3 ];
		MapQuad_r( lm, info, dv2, plane, stv, ttv );
	}
}