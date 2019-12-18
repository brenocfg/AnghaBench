#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ planenum; int cluster; int area; TYPE_1__* brushlist; scalar_t__ areaportal; scalar_t__ opaque; struct TYPE_6__** children; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_7__ {int* portalareas; int brushNum; } ;
typedef  TYPE_3__ brush_t ;
struct TYPE_5__ {TYPE_3__* original; } ;

/* Variables and functions */
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int) ; 

void CheckAreas_r( node_t *node ){
	brush_t *b;

	if ( node->planenum != PLANENUM_LEAF ) {
		CheckAreas_r( node->children[0] );
		CheckAreas_r( node->children[1] );
		return;
	}

	if ( node->opaque ) {
		return;
	}

	if ( node->cluster != -1 ) {
		if ( node->area == -1 ) {
			Sys_FPrintf( SYS_WRN, "WARNING: cluster %d has area set to -1\n", node->cluster );
		}
	}
	if ( node->areaportal ) {
		b = node->brushlist->original;

		// check if the areaportal touches two areas
		if ( b->portalareas[0] == -1 || b->portalareas[1] == -1 ) {
			Sys_FPrintf( SYS_WRN, "WARNING: areaportal brush %i doesn't touch two areas\n", b->brushNum );
		}
	}
}