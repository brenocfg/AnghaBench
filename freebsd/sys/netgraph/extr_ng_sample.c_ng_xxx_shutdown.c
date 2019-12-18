#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xxx_p ;
typedef  TYPE_2__* node_p ;
struct TYPE_11__ {int nd_flags; } ;
struct TYPE_10__ {TYPE_2__* node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int NGF_REALLY_DIE ; 
 TYPE_1__* NG_NODE_PRIVATE (TYPE_2__*) ; 
 int /*<<< orphan*/  NG_NODE_REVIVE (TYPE_2__*) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_xxx_shutdown(node_p node)
{
	const xxx_p privdata = NG_NODE_PRIVATE(node);

#ifndef PERSISTANT_NODE
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);
	free(privdata, M_NETGRAPH);
#else
	if (node->nd_flags & NGF_REALLY_DIE) {
		/*
		 * WE came here because the widget card is being unloaded,
		 * so stop being persistent.
		 * Actually undo all the things we did on creation.
		 */
		NG_NODE_SET_PRIVATE(node, NULL);
		NG_NODE_UNREF(privdata->node);
		free(privdata, M_NETGRAPH);
		return (0);
	}
	NG_NODE_REVIVE(node);		/* tell ng_rmnode() we will persist */
#endif /* PERSISTANT_NODE */
	return (0);
}