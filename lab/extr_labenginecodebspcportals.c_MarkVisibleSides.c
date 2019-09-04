#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_8__ {int numsides; TYPE_1__* original_sides; } ;
typedef  TYPE_3__ mapbrush_t ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  MarkVisibleSides_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFL_VISIBLE ; 
 TYPE_3__* mapbrushes ; 

void MarkVisibleSides(tree_t *tree, int startbrush, int endbrush)
{
	int		i, j;
	mapbrush_t	*mb;
	int		numsides;

	Log_Print("--- MarkVisibleSides ---\n");

	// clear all the visible flags
	for (i=startbrush ; i<endbrush ; i++)
	{
		mb = &mapbrushes[i];

		numsides = mb->numsides;
		for (j=0 ; j<numsides ; j++)
			mb->original_sides[j].flags &= ~SFL_VISIBLE;
	}

	// set visible flags on the sides that are used by portals
	MarkVisibleSides_r (tree->headnode);
}