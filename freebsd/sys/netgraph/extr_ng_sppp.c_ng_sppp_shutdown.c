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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_4__ {int /*<<< orphan*/  unit; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_SPPP ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpfdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_sppp_free_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sppp_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_sppp_shutdown (node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	/* Detach from the packet filter list of interfaces. */
	bpfdetach (priv->ifp);
	sppp_detach (priv->ifp);
	if_detach (priv->ifp);
	if_free(priv->ifp);
	ng_sppp_free_unit (priv->unit);
	free (priv, M_NETGRAPH_SPPP);
	NG_NODE_SET_PRIVATE (node, NULL);
	NG_NODE_UNREF (node);
	return (0);
}