#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hookpriv_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int /*<<< orphan*/ * lower; int /*<<< orphan*/ * ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_L2TP ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/  const) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/  const) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static int
ng_l2tp_disconnect(hook_p hook)
{
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);

	/* Zero out hook pointer */
	if (hook == priv->ctrl)
		priv->ctrl = NULL;
	else if (hook == priv->lower)
		priv->lower = NULL;
	else {
		const hookpriv_p hpriv = NG_HOOK_PRIVATE(hook);
		LIST_REMOVE(hpriv, sessions);
		free(hpriv, M_NETGRAPH_L2TP);
		NG_HOOK_SET_PRIVATE(hook, NULL);
	}

	/* Go away if no longer connected to anything */
	if (NG_NODE_NUMHOOKS(node) == 0 && NG_NODE_IS_VALID(node))
		ng_rmnode_self(node);
	return (0);
}