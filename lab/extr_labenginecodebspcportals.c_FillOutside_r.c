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
struct TYPE_3__ {scalar_t__ planenum; int contents; int /*<<< orphan*/  occupied; struct TYPE_3__** children; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int CONTENTS_SOLID ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  c_inside ; 
 int /*<<< orphan*/  c_outside ; 
 int /*<<< orphan*/  c_solid ; 

void FillOutside_r (node_t *node)
{
	if (node->planenum != PLANENUM_LEAF)
	{
		FillOutside_r (node->children[0]);
		FillOutside_r (node->children[1]);
		return;
	} //end if
	// anything not reachable by an entity
	// can be filled away (by setting solid contents)
	if (!node->occupied)
	{
		if (!(node->contents & CONTENTS_SOLID))
		{
			c_outside++;
			node->contents |= CONTENTS_SOLID;
		} //end if
		else
		{
			c_solid++;
		} //end else
	} //end if
	else
	{
		c_inside++;
	} //end else
}