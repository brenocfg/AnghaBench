#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int compileFlags; TYPE_3__** nodes; struct TYPE_8__** next; } ;
typedef  TYPE_2__ portal_t ;
struct TYPE_9__ {int area; int cluster; TYPE_2__* portals; scalar_t__ skybox; TYPE_1__* brushlist; scalar_t__ areaportal; } ;
typedef  TYPE_3__ node_t ;
struct TYPE_10__ {void** portalareas; int /*<<< orphan*/  brushNum; } ;
typedef  TYPE_4__ brush_t ;
struct TYPE_7__ {TYPE_4__* original; } ;

/* Variables and functions */
 int C_AREAPORTAL ; 
 int /*<<< orphan*/  PortalPassable (TYPE_2__*) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* c_areas ; 
 void* skyboxArea ; 

void FloodAreas_r( node_t *node ){
	int s;
	portal_t    *p;
	brush_t     *b;


	if ( node->areaportal ) {
		if ( node->area == -1 ) {
			node->area = c_areas;
		}

		/* this node is part of an area portal brush */
		b = node->brushlist->original;

		/* if the current area has already touched this portal, we are done */
		if ( b->portalareas[ 0 ] == c_areas || b->portalareas[ 1 ] == c_areas ) {
			return;
		}

		// note the current area as bounding the portal
		if ( b->portalareas[ 1 ] != -1 ) {
			Sys_FPrintf( SYS_WRN, "WARNING: areaportal brush %i touches > 2 areas\n", b->brushNum );
			return;
		}
		if ( b->portalareas[ 0 ] != -1 ) {
			b->portalareas[ 1 ] = c_areas;
		}
		else{
			b->portalareas[ 0 ] = c_areas;
		}

		return;
	}

	if ( node->area != -1 ) {
		return;
	}
	if ( node->cluster == -1 ) {
		return;
	}

	node->area = c_areas;

	/* ydnar: skybox nodes set the skybox area */
	if ( node->skybox ) {
		skyboxArea = c_areas;
	}

	for ( p = node->portals; p; p = p->next[ s ] )
	{
		s = ( p->nodes[1] == node );

		/* ydnar: allow areaportal portals to block area flow */
		if ( p->compileFlags & C_AREAPORTAL ) {
			continue;
		}

		if ( !PortalPassable( p ) ) {
			continue;
		}

		FloodAreas_r( p->nodes[ !s ] );
	}
}