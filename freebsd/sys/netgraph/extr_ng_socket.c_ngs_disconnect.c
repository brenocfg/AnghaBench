#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ngsock {int flags; TYPE_2__* datasock; } ;
struct hookpriv {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {TYPE_1__* ng_socket; } ;
struct TYPE_3__ {int /*<<< orphan*/  so_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct hookpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_SOCK ; 
 int NGS_FLAG_NOLINGER ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 struct hookpriv* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 struct ngsock* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_ISCONNECTED ; 
 int /*<<< orphan*/  free (struct hookpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngs_disconnect(hook_p hook)
{
	node_p node = NG_HOOK_NODE(hook);
	struct ngsock *const priv = NG_NODE_PRIVATE(node);
	struct hookpriv *hp = NG_HOOK_PRIVATE(hook);

	LIST_REMOVE(hp, next);
	free(hp, M_NETGRAPH_SOCK);

	if ((priv->datasock) && (priv->datasock->ng_socket)) {
		if (NG_NODE_NUMHOOKS(node) == 1)
			priv->datasock->ng_socket->so_state |= SS_ISCONNECTED;
		else
			priv->datasock->ng_socket->so_state &= ~SS_ISCONNECTED;
	}

	if ((priv->flags & NGS_FLAG_NOLINGER) &&
	    (NG_NODE_NUMHOOKS(node) == 0) && (NG_NODE_IS_VALID(node)))
		ng_rmnode_self(node);

	return (0);
}