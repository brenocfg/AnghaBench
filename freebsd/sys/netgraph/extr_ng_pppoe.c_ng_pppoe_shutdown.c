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
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_6__ {int /*<<< orphan*/  node; TYPE_1__* sesshash; } ;
struct TYPE_5__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_PPPOE ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int SESSHASHSIZE ; 
 int /*<<< orphan*/  free (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_pppoe_shutdown(node_p node)
{
	const priv_p privp = NG_NODE_PRIVATE(node);
	int	i;

	for (i = 0; i < SESSHASHSIZE; i++)
	    mtx_destroy(&privp->sesshash[i].mtx);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(privp->node);
	free(privp, M_NETGRAPH_PPPOE);
	return (0);
}