#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_12__ {TYPE_4__* brushes; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_13__ {int numsides; TYPE_1__* sides; int /*<<< orphan*/  detail; struct TYPE_13__* next; } ;
typedef  TYPE_4__ brush_t ;
struct TYPE_10__ {int /*<<< orphan*/  visible; scalar_t__ winding; } ;

/* Variables and functions */
 TYPE_4__* CopyBrush (TYPE_4__*) ; 
 int FilterBrushIntoTree_r (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  qtrue ; 

void FilterDetailBrushesIntoTree( entity_t *e, tree_t *tree ){
	brush_t             *b, *newb;
	int r;
	int c_unique, c_clusters;
	int i;


	/* note it */
	Sys_FPrintf( SYS_VRB,  "--- FilterDetailBrushesIntoTree ---\n" );

	/* walk the list of brushes */
	c_unique = 0;
	c_clusters = 0;
	for ( b = e->brushes; b; b = b->next )
	{
		if ( !b->detail ) {
			continue;
		}
		c_unique++;
		newb = CopyBrush( b );
		r = FilterBrushIntoTree_r( newb, tree->headnode );
		c_clusters += r;

		/* mark all sides as visible so drawsurfs are created */
		if ( r ) {
			for ( i = 0; i < b->numsides; i++ )
			{
				if ( b->sides[ i ].winding ) {
					b->sides[ i ].visible = qtrue;
				}
			}
		}
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d detail brushes\n", c_unique );
	Sys_FPrintf( SYS_VRB, "%9d cluster references\n", c_clusters );
}