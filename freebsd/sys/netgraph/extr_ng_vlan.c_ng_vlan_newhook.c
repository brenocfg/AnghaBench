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
typedef  void* hook_p ;
struct TYPE_3__ {void* nomatch_hook; void* downstream_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,int /*<<< orphan*/ *) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_VLAN_HOOK_DOWNSTREAM ; 
 int /*<<< orphan*/  NG_VLAN_HOOK_NOMATCH ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_vlan_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_VLAN_HOOK_DOWNSTREAM) == 0)
		priv->downstream_hook = hook;
	else if (strcmp(name, NG_VLAN_HOOK_NOMATCH) == 0)
		priv->nomatch_hook = hook;
	else {
		/*
		 * Any other hook name is valid and can
		 * later be associated with a filter rule.
		 */
	}
	NG_HOOK_SET_PRIVATE(hook, NULL);
	return (0);
}