#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_16__ {size_t planenum; } ;
typedef  TYPE_2__ side_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_17__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;
struct TYPE_18__ {int /*<<< orphan*/  mapBrush; int /*<<< orphan*/  fogNum; TYPE_1__* sideRef; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
typedef  int /*<<< orphan*/  entity_t ;
struct TYPE_19__ {int numsides; TYPE_2__* sides; } ;
typedef  TYPE_5__ brush_t ;
struct TYPE_15__ {TYPE_2__* side; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearSurface (TYPE_4__*) ; 
 int /*<<< orphan*/  ClipWindingEpsilon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 TYPE_4__* DrawSurfaceForSide (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int MAX_BRUSH_SIDES ; 
 int /*<<< orphan*/  ON_EPSILON ; 
 int /*<<< orphan*/ * WindingFromDrawSurf (TYPE_4__*) ; 
 TYPE_3__* mapplanes ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int numFogFragments ; 
 int /*<<< orphan*/  numMapDrawSurfs ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ChopFaceSurfaceByBrush( entity_t *e, mapDrawSurface_t *ds, brush_t *b ){
	int i, j;
	side_t              *s;
	plane_t             *plane;
	winding_t           *w;
	winding_t           *front, *back;
	winding_t           *outside[ MAX_BRUSH_SIDES ];
	int numOutside;
	mapDrawSurface_t    *newds;


	/* dummy check */
	if ( ds->sideRef == NULL || ds->sideRef->side == NULL ) {
		return qfalse;
	}

	/* initial setup */
	w = WindingFromDrawSurf( ds );
	numOutside = 0;

	/* chop by each brush side */
	for ( i = 0; i < b->numsides; i++ )
	{
		/* get brush side and plane */
		s = &b->sides[ i ];
		plane = &mapplanes[ s->planenum ];

		/* handle coplanar outfacing (don't fog) */
		if ( ds->sideRef->side->planenum == s->planenum ) {
			return qfalse;
		}

		/* handle coplanar infacing (keep inside) */
		if ( ( ds->sideRef->side->planenum ^ 1 ) == s->planenum ) {
			continue;
		}

		/* general case */
		ClipWindingEpsilon( w, plane->normal, plane->dist, ON_EPSILON, &front, &back );
		FreeWinding( w );

		if ( back == NULL ) {
			/* nothing actually contained inside */
			for ( j = 0; j < numOutside; j++ )
				FreeWinding( outside[ j ] );
			return qfalse;
		}

		if ( front != NULL ) {
			if ( numOutside == MAX_BRUSH_SIDES ) {
				Error( "MAX_BRUSH_SIDES" );
			}
			outside[ numOutside ] = front;
			numOutside++;
		}

		w = back;
	}

	/* fixme: celshaded surface fragment errata */

	/* all of outside fragments become seperate drawsurfs */
	numFogFragments += numOutside;
	s = ds->sideRef->side;
	for ( i = 0; i < numOutside; i++ )
	{
		newds = DrawSurfaceForSide( e, ds->mapBrush, s, outside[ i ] );
		newds->fogNum = ds->fogNum;
		FreeWinding( outside[ i ] );
	}

	/* ydnar: the old code neglected to snap to 0.125 for the fragment
	          inside the fog brush, leading to sparklies. this new code does
	          the right thing and uses the original surface's brush side */

	/* build a drawsurf for it */
	newds = DrawSurfaceForSide( e, ds->mapBrush, s, w );
	if ( newds == NULL ) {
		return qfalse;
	}

	/* copy new to original */
	ClearSurface( ds );
	memcpy( ds, newds, sizeof( mapDrawSurface_t ) );

	/* didn't really add a new drawsurface... :) */
	numMapDrawSurfs--;

	/* return ok */
	return qtrue;
}