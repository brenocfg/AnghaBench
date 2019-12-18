#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ planenum; int contents; struct TYPE_3__** children; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int CONTENTS_SOLID ; 
 scalar_t__ PLANENUM_LEAF ; 

int ClusterContents (node_t *node)
{
	int		c1, c2, c;

	if (node->planenum == PLANENUM_LEAF)
		return node->contents;

	c1 = ClusterContents(node->children[0]);
	c2 = ClusterContents(node->children[1]);
	c = c1|c2;

	// a cluster may include some solid detail areas, but
	// still be seen into
	if ( ! (c1&CONTENTS_SOLID) || ! (c2&CONTENTS_SOLID) )
		c &= ~CONTENTS_SOLID;
	return c;
}