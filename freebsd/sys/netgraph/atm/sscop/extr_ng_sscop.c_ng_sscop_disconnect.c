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
struct priv {int /*<<< orphan*/  sscop; scalar_t__ enabled; int /*<<< orphan*/ * lower; int /*<<< orphan*/ * upper; int /*<<< orphan*/ * manage; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ SSCOP_IDLE ; 
 int /*<<< orphan*/  SSCOP_RELEASE_request ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_aasig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sscop_getstate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_sscop_disconnect(hook_p hook)
{
	node_p node = NG_HOOK_NODE(hook);
	struct priv *priv = NG_NODE_PRIVATE(node);

	if(hook == priv->upper)
		priv->upper = NULL;
	else if(hook == priv->lower)
		priv->lower = NULL;
	else if(hook == priv->manage)
		priv->manage = NULL;

	if(NG_NODE_NUMHOOKS(node) == 0) {
		if(NG_NODE_IS_VALID(node))
			ng_rmnode_self(node);
	} else {
		/*
		 * Imply a release request, if the upper layer is
		 * disconnected.
		 */
		if(priv->upper == NULL && priv->lower != NULL &&
		   priv->enabled &&
		   sscop_getstate(priv->sscop) != SSCOP_IDLE) {
			sscop_aasig(priv->sscop, SSCOP_RELEASE_request,
			    NULL, 0);
		}
	}
	return 0;
}