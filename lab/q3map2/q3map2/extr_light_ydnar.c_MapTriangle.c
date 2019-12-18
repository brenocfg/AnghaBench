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
typedef  int /*<<< orphan*/ * vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_16__ {TYPE_1__* si; } ;
typedef  TYPE_2__ surfaceInfo_t ;
struct TYPE_17__ {int /*<<< orphan*/ * plane; } ;
typedef  TYPE_3__ rawLightmap_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_18__ {float** lightmap; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_4__ bspDrawVert_t ;
struct TYPE_15__ {int /*<<< orphan*/ * normalImage; } ;

/* Variables and functions */
 scalar_t__ CalcTangentVectors (int,TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MapSingleLuxel (TYPE_3__*,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MapTriangle_r (TYPE_3__*,TYPE_2__*,TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PlaneFromPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float fabs (float) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

__attribute__((used)) static qboolean MapTriangle( rawLightmap_t *lm, surfaceInfo_t *info, bspDrawVert_t *dv[ 3 ], qboolean mapNonAxial ){
	int i;
	vec4_t plane;
	vec3_t          *stv, *ttv, stvStatic[ 3 ], ttvStatic[ 3 ];


	/* get plane if possible */
	if ( lm->plane != NULL ) {
		VectorCopy( lm->plane, plane );
		plane[ 3 ] = lm->plane[ 3 ];
	}

	/* otherwise make one from the points */
	else if ( PlaneFromPoints( plane, dv[ 0 ]->xyz, dv[ 1 ]->xyz, dv[ 2 ]->xyz ) == qfalse ) {
		return qfalse;
	}

	/* check to see if we need to calculate texture->world tangent vectors */
	if ( info->si->normalImage != NULL && CalcTangentVectors( 3, dv, stvStatic, ttvStatic ) ) {
		stv = stvStatic;
		ttv = ttvStatic;
	}
	else
	{
		stv = NULL;
		ttv = NULL;
	}

	/* map the vertexes */
	MapSingleLuxel( lm, info, dv[ 0 ], plane, 1, stv, ttv );
	MapSingleLuxel( lm, info, dv[ 1 ], plane, 1, stv, ttv );
	MapSingleLuxel( lm, info, dv[ 2 ], plane, 1, stv, ttv );

	/* 2002-11-20: prefer axial triangle edges */
	if ( mapNonAxial ) {
		/* subdivide the triangle */
		MapTriangle_r( lm, info, dv, plane, stv, ttv );
		return qtrue;
	}

	for ( i = 0; i < 3; i++ )
	{
		float           *a, *b;
		bspDrawVert_t   *dv2[ 3 ];


		/* get verts */
		a = dv[ i ]->lightmap[ 0 ];
		b = dv[ ( i + 1 ) % 3 ]->lightmap[ 0 ];

		/* make degenerate triangles for mapping edges */
		if ( fabs( a[ 0 ] - b[ 0 ] ) < 0.01f || fabs( a[ 1 ] - b[ 1 ] ) < 0.01f ) {
			dv2[ 0 ] = dv[ i ];
			dv2[ 1 ] = dv[ ( i + 1 ) % 3 ];
			dv2[ 2 ] = dv[ ( i + 1 ) % 3 ];

			/* map the degenerate triangle */
			MapTriangle_r( lm, info, dv2, plane, stv, ttv );
		}
	}

	return qtrue;
}