#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_5__ {int /*<<< orphan*/  xmtx; int /*<<< orphan*/  rmtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_PPP ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_ppp_frag_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ppp_stop_frag_timer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ppp_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	/* Stop fragment queue timer */
	ng_ppp_stop_frag_timer(node);

	/* Take down netgraph node */
	ng_ppp_frag_reset(node);
	mtx_destroy(&priv->rmtx);
	mtx_destroy(&priv->xmtx);
	bzero(priv, sizeof(*priv));
	free(priv, M_NETGRAPH_PPP);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);		/* let the node escape */
	return (0);
}