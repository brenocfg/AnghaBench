#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_6__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; TYPE_4__ readq; int /*<<< orphan*/  ngd_mtx; int /*<<< orphan*/  ngddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG ; 
 int /*<<< orphan*/  IF_DRAIN (TYPE_4__*) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngd_unit ; 

__attribute__((used)) static int
ng_device_disconnect(hook_p hook)
{
	priv_p priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	DBG;

	destroy_dev(priv->ngddev);
	mtx_destroy(&priv->ngd_mtx);

	IF_DRAIN(&priv->readq);
	mtx_destroy(&(priv)->readq.ifq_mtx);

	free_unr(ngd_unit, priv->unit);

	free(priv, M_NETGRAPH);

	ng_rmnode_self(NG_HOOK_NODE(hook));

	return(0);
}