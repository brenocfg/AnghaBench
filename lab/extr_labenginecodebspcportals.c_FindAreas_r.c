#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ planenum; int contents; int /*<<< orphan*/  occupied; scalar_t__ area; struct TYPE_4__** children; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int CONTENTS_AREAPORTAL ; 
 int CONTENTS_SOLID ; 
 int /*<<< orphan*/  FloodAreas_r (TYPE_1__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  c_areas ; 

void FindAreas_r (node_t *node)
{
	if (node->planenum != PLANENUM_LEAF)
	{
		FindAreas_r (node->children[0]);
		FindAreas_r (node->children[1]);
		return;
	}

	if (node->area)
		return;		// allready got it

	if (node->contents & CONTENTS_SOLID)
		return;

	if (!node->occupied)
		return;			// not reachable by entities

	// area portals are allways only flooded into, never
	// out of
	if (node->contents == CONTENTS_AREAPORTAL)
		return;

	c_areas++;
	FloodAreas_r (node);
}