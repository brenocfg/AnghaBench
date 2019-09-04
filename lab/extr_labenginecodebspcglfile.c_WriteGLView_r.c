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
struct TYPE_6__ {scalar_t__ planenum; TYPE_1__* portals; struct TYPE_6__** children; } ;
typedef  TYPE_2__ node_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OutputPortal (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ PLANENUM_LEAF ; 

void WriteGLView_r (node_t *node, FILE *glview)
{
	portal_t	*p, *nextp;

	if (node->planenum != PLANENUM_LEAF)
	{
		WriteGLView_r (node->children[0], glview);
		WriteGLView_r (node->children[1], glview);
		return;
	}

	// write all the portals
	for (p=node->portals ; p ; p=nextp)
	{
		if (p->nodes[0] == node)
		{
			OutputPortal (p, glview);
			nextp = p->next[0];
		}
		else
			nextp = p->next[1];
	}
}