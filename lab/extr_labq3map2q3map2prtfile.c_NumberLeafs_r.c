#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__** next; TYPE_2__** nodes; } ;
typedef  TYPE_1__ portal_t ;
struct TYPE_6__ {scalar_t__ planenum; int cluster; int area; TYPE_1__* portals; scalar_t__ opaque; struct TYPE_6__** children; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 scalar_t__ PLANENUM_LEAF ; 
 scalar_t__ PortalPassable (TYPE_1__*) ; 
 int /*<<< orphan*/  num_solidfaces ; 
 int num_visclusters ; 
 int /*<<< orphan*/  num_visportals ; 

void NumberLeafs_r( node_t *node ){
	portal_t    *p;

	if ( node->planenum != PLANENUM_LEAF ) {
		// decision node
		node->cluster = -99;
		NumberLeafs_r( node->children[0] );
		NumberLeafs_r( node->children[1] );
		return;
	}

	node->area = -1;

	if ( node->opaque ) {
		// solid block, viewpoint never inside
		node->cluster = -1;
		return;
	}

	node->cluster = num_visclusters;
	num_visclusters++;

	// count the portals
	for ( p = node->portals ; p ; )
	{
		if ( p->nodes[0] == node ) {      // only write out from first leaf
			if ( PortalPassable( p ) ) {
				num_visportals++;
			}
			else{
				num_solidfaces++;
			}
			p = p->next[0];
		}
		else
		{
			if ( !PortalPassable( p ) ) {
				num_solidfaces++;
			}
			p = p->next[1];
		}
	}
}