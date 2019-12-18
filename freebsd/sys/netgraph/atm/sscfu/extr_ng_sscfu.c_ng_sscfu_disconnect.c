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
struct priv {int /*<<< orphan*/  sscf; scalar_t__ enabled; int /*<<< orphan*/ * lower; int /*<<< orphan*/ * upper; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ SSCFU_RELEASED ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 
 scalar_t__ sscfu_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscfu_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_sscfu_disconnect(hook_p hook)
{
	node_p node = NG_HOOK_NODE(hook);
	struct priv *priv = NG_NODE_PRIVATE(node);

	if (hook == priv->upper)
		priv->upper = NULL;
	else if (hook == priv->lower)
		priv->lower = NULL;
	else {
		log(LOG_ERR, "bogus hook");
		return (EINVAL);
	}

	if (NG_NODE_NUMHOOKS(node) == 0) {
		if (NG_NODE_IS_VALID(node))
			ng_rmnode_self(node);
	} else {
		/*
		 * Because there are no timeouts reset the protocol
		 * if the lower layer is disconnected.
		 */
		if (priv->lower == NULL &&
		    priv->enabled &&
		    sscfu_getstate(priv->sscf) != SSCFU_RELEASED)
			sscfu_reset(priv->sscf);
	}
	return (0);
}