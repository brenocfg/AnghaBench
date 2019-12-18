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
typedef  int /*<<< orphan*/  link_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {int /*<<< orphan*/  persistent; int /*<<< orphan*/  numLinks; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH_BRIDGE ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_bridge_remove_hosts (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bridge_disconnect(hook_p hook)
{
	const priv_p priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	link_p link = NG_HOOK_PRIVATE(hook);

	/* Remove all hosts associated with this link */
	ng_bridge_remove_hosts(priv, link);

	/* Free associated link information */
	free(link, M_NETGRAPH_BRIDGE);
	priv->numLinks--;

	/* If no more hooks, go away */
	if ((NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0)
	    && (NG_NODE_IS_VALID(NG_HOOK_NODE(hook)))
	    && !priv->persistent) {
		ng_rmnode_self(NG_HOOK_NODE(hook));
	}
	return (0);
}