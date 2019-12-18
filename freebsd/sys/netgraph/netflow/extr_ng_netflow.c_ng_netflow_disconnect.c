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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_2__* iface_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_6__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * hook; } ;
struct TYPE_5__ {int /*<<< orphan*/ * export9; int /*<<< orphan*/  exp_callout; int /*<<< orphan*/ * export; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 TYPE_2__* NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_netflow_disconnect(hook_p hook)
{
	node_p node = NG_HOOK_NODE(hook);
	priv_p priv = NG_NODE_PRIVATE(node);
	iface_p iface = NG_HOOK_PRIVATE(hook);

	if (iface != NULL) {
		if (iface->hook == hook)
			iface->hook = NULL;
		if (iface->out == hook)
			iface->out = NULL;
	}

	/* if export hook disconnected stop running expire(). */
	if (hook == priv->export) {
		if (priv->export9 == NULL)
			callout_drain(&priv->exp_callout);
		priv->export = NULL;
	}

	if (hook == priv->export9) {
		if (priv->export == NULL)
			callout_drain(&priv->exp_callout);
		priv->export9 = NULL;
	}

	/* Removal of the last link destroys the node. */
	if (NG_NODE_NUMHOOKS(node) == 0)
		ng_rmnode_self(node);

	return (0);
}