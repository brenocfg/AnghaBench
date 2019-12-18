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
struct TYPE_3__ {void* uplink; void* downlink; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_UI_HOOK_DOWNSTREAM ; 
 int /*<<< orphan*/  NG_UI_HOOK_UPSTREAM ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_UI_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (!strcmp(name, NG_UI_HOOK_DOWNSTREAM)) {
		if (priv->downlink)
			return (EISCONN);
		priv->downlink = hook;
	} else if (!strcmp(name, NG_UI_HOOK_UPSTREAM)) {
		if (priv->uplink)
			return (EISCONN);
		priv->uplink = hook;
	} else
		return (EINVAL);
	return (0);
}