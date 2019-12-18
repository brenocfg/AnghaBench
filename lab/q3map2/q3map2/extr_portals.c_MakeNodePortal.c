#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_8__ {int /*<<< orphan*/  compileFlags; int /*<<< orphan*/ * winding; TYPE_2__* onnode; TYPE_3__ plane; TYPE_2__** nodes; struct TYPE_8__** next; } ;
typedef  TYPE_1__ portal_t ;
struct TYPE_9__ {size_t planenum; int /*<<< orphan*/ * children; int /*<<< orphan*/  compileFlags; TYPE_1__* portals; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddPortalToNodes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AllocPortal () ; 
 int /*<<< orphan*/ * BaseWindingForNode (TYPE_2__*) ; 
 int /*<<< orphan*/  CLIP_EPSILON ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ FixWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WindingIsTiny (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_badportals ; 
 int /*<<< orphan*/  c_tinyportals ; 
 TYPE_3__* mapplanes ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  vec3_origin ; 

void MakeNodePortal( node_t *node ){
	portal_t    *new_portal, *p;
	winding_t   *w;
	vec3_t normal;
	float dist;
	int side;

	w = BaseWindingForNode( node );

	// clip the portal by all the other portals in the node
	for ( p = node->portals ; p && w; p = p->next[side] )
	{
		if ( p->nodes[0] == node ) {
			side = 0;
			VectorCopy( p->plane.normal, normal );
			dist = p->plane.dist;
		}
		else if ( p->nodes[1] == node ) {
			side = 1;
			VectorSubtract( vec3_origin, p->plane.normal, normal );
			dist = -p->plane.dist;
		}
		else{
			Error( "CutNodePortals_r: mislinked portal" );
		}

		ChopWindingInPlace( &w, normal, dist, CLIP_EPSILON );
	}

	if ( !w ) {
		return;
	}


	/* ydnar: adding this here to fix degenerate windings */
	#if 0
	if ( FixWinding( w ) == qfalse ) {
		c_badportals++;
		FreeWinding( w );
		return;
	}
	#endif

	if ( WindingIsTiny( w ) ) {
		c_tinyportals++;
		FreeWinding( w );
		return;
	}

	new_portal = AllocPortal();
	new_portal->plane = mapplanes[node->planenum];
	new_portal->onnode = node;
	new_portal->winding = w;
	new_portal->compileFlags = node->compileFlags;
	AddPortalToNodes( new_portal, node->children[0], node->children[1] );
}