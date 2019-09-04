#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * bounds; int /*<<< orphan*/  (* storeLeafs ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ leafList_t ;
typedef  int /*<<< orphan*/  cplane_t ;
struct TYPE_7__ {int* children; int /*<<< orphan*/ * plane; } ;
typedef  TYPE_2__ cNode_t ;
struct TYPE_8__ {TYPE_2__* nodes; } ;

/* Variables and functions */
 int BoxOnPlaneSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__ cm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

void CM_BoxLeafnums_r( leafList_t *ll, int nodenum ) {
	cplane_t	*plane;
	cNode_t		*node;
	int			s;

	while (1) {
		if (nodenum < 0) {
			ll->storeLeafs( ll, nodenum );
			return;
		}
	
		node = &cm.nodes[nodenum];
		plane = node->plane;
		s = BoxOnPlaneSide( ll->bounds[0], ll->bounds[1], plane );
		if (s == 1) {
			nodenum = node->children[0];
		} else if (s == 2) {
			nodenum = node->children[1];
		} else {
			// go down both
			CM_BoxLeafnums_r( ll, node->children[0] );
			nodenum = node->children[1];
		}

	}
}