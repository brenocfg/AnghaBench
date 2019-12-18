#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccnode {int /*<<< orphan*/  hook_cnt; int /*<<< orphan*/  data; int /*<<< orphan*/ * manage; int /*<<< orphan*/ * dump; } ;
struct cchook {TYPE_1__* node; int /*<<< orphan*/  inst; scalar_t__ is_uni; } ;
struct ccdata {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_2__ {struct ccdata* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NG_CCATM ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 struct cchook* NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 struct ccnode* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_port_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_unmanage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_user_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_work (struct ccdata*) ; 
 int /*<<< orphan*/  free (struct cchook*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ccatm_disconnect(hook_p hook)
{
	node_p node = NG_HOOK_NODE(hook);
	struct ccnode *priv = NG_NODE_PRIVATE(node);
	struct cchook *hd = NG_HOOK_PRIVATE(hook);
	struct ccdata *cc;

	if (hook == priv->dump) {
		priv->dump = NULL;

	} else if (hook == priv->manage) {
		priv->manage = NULL;
		cc_unmanage(priv->data);

	} else {
		if (hd->is_uni)
			cc_port_destroy(hd->inst, 0);
		else
			cc_user_destroy(hd->inst);

		cc = hd->node->data;

		free(hd, M_NG_CCATM);
		NG_HOOK_SET_PRIVATE(hook, NULL);

		priv->hook_cnt--;

		cc_work(cc);
	}

	/*
	 * When the number of hooks drops to zero, delete the node.
	 */
	if (NG_NODE_NUMHOOKS(node) == 0 && NG_NODE_IS_VALID(node))
		ng_rmnode_self(node);

	return (0);
}