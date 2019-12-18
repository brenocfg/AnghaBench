#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  priv_p ;
typedef  TYPE_1__* node_p ;
struct TYPE_7__ {int nd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int NGF_REALLY_DIE ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NODE_REVIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_gif_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (node->nd_flags & NGF_REALLY_DIE) {
		/*
		 * WE came here because the gif interface is being destroyed,
		 * so stop being persistent.
		 * Actually undo all the things we did on creation.
		 * Assume the ifp has already been freed.
		 */
		NG_NODE_SET_PRIVATE(node, NULL);
		free(priv, M_NETGRAPH);		
		NG_NODE_UNREF(node);	/* free node itself */
		return (0);
	}
	NG_NODE_REVIVE(node);		/* Signal ng_rmnode we are persisant */
	return (0);
}