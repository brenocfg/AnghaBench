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
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int /*<<< orphan*/ ** vlan_hook; int /*<<< orphan*/ * nomatch_hook; int /*<<< orphan*/ * downstream_hook; } ;

/* Variables and functions */
 size_t EVL_VLANOFTAG (uintptr_t) ; 
 scalar_t__ IS_HOOK_VLAN_SET (uintptr_t) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_vlan_disconnect(hook_p hook)
{
	const priv_p priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	uintptr_t hook_data;

	if (hook == priv->downstream_hook)
		priv->downstream_hook = NULL;
	else if (hook == priv->nomatch_hook)
		priv->nomatch_hook = NULL;
	else {
		/* Purge a rule that refers to this hook. */
		hook_data = (uintptr_t)NG_HOOK_PRIVATE(hook);
		if (IS_HOOK_VLAN_SET(hook_data))
			priv->vlan_hook[EVL_VLANOFTAG(hook_data)] = NULL;
	}
	NG_HOOK_SET_PRIVATE(hook, NULL);
	if ((NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0) &&
	    (NG_NODE_IS_VALID(NG_HOOK_NODE(hook))))
		ng_rmnode_self(NG_HOOK_NODE(hook));
	return (0);
}