#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ng_atmllc_priv {int /*<<< orphan*/ * fddi; int /*<<< orphan*/ * ether; int /*<<< orphan*/ * atm; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 struct ng_atmllc_priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_atmllc_disconnect(hook_p hook)
{
	node_p	node;
	struct	ng_atmllc_priv *priv;

	node = NG_HOOK_NODE(hook);
	priv = NG_NODE_PRIVATE(node);

	if (hook == priv->atm) {
		priv->atm = NULL;
	} else if (hook == priv->ether) {
		priv->ether = NULL;
	} else if (hook == priv->fddi) {
		priv->fddi = NULL;
	}

	if (NG_NODE_NUMHOOKS(node) == 0 && NG_NODE_IS_VALID(node)) {
		ng_rmnode_self(node);
	}

	return (0);
}