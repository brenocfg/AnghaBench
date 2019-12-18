#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_8__ {int /*<<< orphan*/  if_vnet; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  unit; TYPE_2__* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_IFACE ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ng_iface_unit ; 
 int /*<<< orphan*/  bpfdetach (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  if_free (TYPE_2__*) ; 
 int /*<<< orphan*/  rm_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_iface_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	/*
	 * The ifnet may be in a different vnet than the netgraph node, 
	 * hence we have to change the current vnet context here.
	 */
	CURVNET_SET_QUIET(priv->ifp->if_vnet);
	bpfdetach(priv->ifp);
	if_detach(priv->ifp);
	if_free(priv->ifp);
	CURVNET_RESTORE();
	priv->ifp = NULL;
	free_unr(V_ng_iface_unit, priv->unit);
	rm_destroy(&priv->lock);
	free(priv, M_NETGRAPH_IFACE);
	NG_NODE_SET_PRIVATE(node, NULL);
	NG_NODE_UNREF(node);
	return (0);
}