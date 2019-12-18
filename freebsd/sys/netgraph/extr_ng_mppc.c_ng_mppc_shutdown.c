#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_8__ {TYPE_3__* const history; } ;
struct TYPE_7__ {TYPE_3__* const history; } ;
struct TYPE_9__ {TYPE_2__ recv; TYPE_1__ xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_MPPC ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__* const,int) ; 
 int /*<<< orphan*/  free (TYPE_3__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_mppc_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	/* Take down netgraph node */
#ifdef NETGRAPH_MPPC_COMPRESSION
	if (priv->xmit.history != NULL)
		free(priv->xmit.history, M_NETGRAPH_MPPC);
	if (priv->recv.history != NULL)
		free(priv->recv.history, M_NETGRAPH_MPPC);
#endif
	bzero(priv, sizeof(*priv));
	free(priv, M_NETGRAPH_MPPC);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);		/* let the node escape */
	return (0);
}