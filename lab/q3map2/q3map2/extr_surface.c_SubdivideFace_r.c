#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  side_t ;
struct TYPE_10__ {int fogNum; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
typedef  int /*<<< orphan*/  entity_t ;
typedef  int /*<<< orphan*/  brush_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  ClearBounds (float*,float*) ; 
 int /*<<< orphan*/  ClipWindingEpsilon (TYPE_1__*,float*,float,float const,TYPE_1__**,TYPE_1__**) ; 
 float DotProduct (float*,float*) ; 
 TYPE_2__* DrawSurfaceForSide (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 float ceil (float) ; 
 float floor (float) ; 

__attribute__((used)) static void SubdivideFace_r( entity_t *e, brush_t *brush, side_t *side, winding_t *w, int fogNum, float subdivisions ){
	int i;
	int axis;
	vec3_t bounds[ 2 ];
	const float epsilon = 0.1;
	int subFloor, subCeil;
	winding_t           *frontWinding, *backWinding;
	mapDrawSurface_t    *ds;


	/* dummy check */
	if ( w == NULL ) {
		return;
	}
	if ( w->numpoints < 3 ) {
		Error( "SubdivideFace_r: Bad w->numpoints (%d < 3)", w->numpoints );
	}

	/* determine surface bounds */
	ClearBounds( bounds[ 0 ], bounds[ 1 ] );
	for ( i = 0; i < w->numpoints; i++ )
		AddPointToBounds( w->p[ i ], bounds[ 0 ], bounds[ 1 ] );

	/* split the face */
	for ( axis = 0; axis < 3; axis++ )
	{
		vec3_t planePoint = { 0, 0, 0 };
		vec3_t planeNormal = { 0, 0, 0 };
		float d;


		/* create an axial clipping plane */
		subFloor = floor( bounds[ 0 ][ axis ] / subdivisions ) * subdivisions;
		subCeil = ceil( bounds[ 1 ][ axis ] / subdivisions ) * subdivisions;
		planePoint[ axis ] = subFloor + subdivisions;
		planeNormal[ axis ] = -1;
		d = DotProduct( planePoint, planeNormal );

		/* subdivide if necessary */
		if ( ( subCeil - subFloor ) > subdivisions ) {
			/* clip the winding */
			ClipWindingEpsilon( w, planeNormal, d, epsilon, &frontWinding, &backWinding );

			/* the clip may not produce two polygons if it was epsilon close */
			if ( frontWinding == NULL ) {
				w = backWinding;
			}
			else if ( backWinding == NULL ) {
				w = frontWinding;
			}
			else
			{
				SubdivideFace_r( e, brush, side, frontWinding, fogNum, subdivisions );
				SubdivideFace_r( e, brush, side, backWinding, fogNum, subdivisions );
				return;
			}
		}
	}

	/* create a face surface */
	ds = DrawSurfaceForSide( e, brush, side, w );

	/* set correct fog num */
	ds->fogNum = fogNum;
}