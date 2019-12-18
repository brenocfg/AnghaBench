#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_12__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
struct TYPE_14__ {TYPE_1__ plane; int /*<<< orphan*/  side; TYPE_4__** nodes; TYPE_2__* winding; struct TYPE_14__** next; } ;
typedef  TYPE_3__ portal_t ;
struct TYPE_15__ {scalar_t__ planenum; TYPE_3__* portals; scalar_t__ opaque; struct TYPE_15__** children; } ;
typedef  TYPE_4__ node_t ;
struct TYPE_16__ {int** lightmapVecs; int fogNum; int numVerts; TYPE_6__* verts; int /*<<< orphan*/  planeNum; int /*<<< orphan*/  sideRef; int /*<<< orphan*/  planar; int /*<<< orphan*/ * shaderInfo; } ;
typedef  TYPE_5__ mapDrawSurface_t ;
struct TYPE_17__ {int* xyz; int* normal; int** color; scalar_t__* st; } ;
typedef  TYPE_6__ bspDrawVert_t ;

/* Variables and functions */
 TYPE_5__* AllocDrawSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AllocSideRef (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 int /*<<< orphan*/  FindFloatPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_LIGHTMAPS ; 
 scalar_t__ PLANENUM_LEAF ; 
 scalar_t__ PortalPassable (TYPE_3__*) ; 
 int /*<<< orphan*/  SURFACE_FACE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * debugColors ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_6__* safe_malloc (int) ; 

__attribute__((used)) static void MakeDebugPortalSurfs_r( node_t *node, shaderInfo_t *si ){
	int i, k, c, s;
	portal_t            *p;
	winding_t           *w;
	mapDrawSurface_t    *ds;
	bspDrawVert_t       *dv;


	/* recurse if decision node */
	if ( node->planenum != PLANENUM_LEAF ) {
		MakeDebugPortalSurfs_r( node->children[ 0 ], si );
		MakeDebugPortalSurfs_r( node->children[ 1 ], si );
		return;
	}

	/* don't bother with opaque leaves */
	if ( node->opaque ) {
		return;
	}

	/* walk the list of portals */
	for ( c = 0, p = node->portals; p != NULL; c++, p = p->next[ s ] )
	{
		/* get winding and side even/odd */
		w = p->winding;
		s = ( p->nodes[ 1 ] == node );

		/* is this a valid portal for this leaf? */
		if ( w && p->nodes[ 0 ] == node ) {
			/* is this portal passable? */
			if ( PortalPassable( p ) == qfalse ) {
				continue;
			}

			/* check max points */
			if ( w->numpoints > 64 ) {
				Error( "MakePortalSurfs_r: w->numpoints = %d", w->numpoints );
			}

			/* allocate a drawsurface */
			ds = AllocDrawSurface( SURFACE_FACE );
			ds->shaderInfo = si;
			ds->planar = qtrue;
			ds->sideRef = AllocSideRef( p->side, NULL );
			ds->planeNum = FindFloatPlane( p->plane.normal, p->plane.dist, 0, NULL );
			VectorCopy( p->plane.normal, ds->lightmapVecs[ 2 ] );
			ds->fogNum = -1;
			ds->numVerts = w->numpoints;
			ds->verts = safe_malloc( ds->numVerts * sizeof( *ds->verts ) );
			memset( ds->verts, 0, ds->numVerts * sizeof( *ds->verts ) );

			/* walk the winding */
			for ( i = 0; i < ds->numVerts; i++ )
			{
				/* get vert */
				dv = ds->verts + i;

				/* set it */
				VectorCopy( w->p[ i ], dv->xyz );
				VectorCopy( p->plane.normal, dv->normal );
				dv->st[ 0 ] = 0;
				dv->st[ 1 ] = 0;
				for ( k = 0; k < MAX_LIGHTMAPS; k++ )
				{
					VectorCopy( debugColors[ c % 12 ], dv->color[ k ] );
					dv->color[ k ][ 3 ] = 32;
				}
			}
		}
	}
}