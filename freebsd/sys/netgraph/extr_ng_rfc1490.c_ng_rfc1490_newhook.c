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
struct TYPE_3__ {void* ethernet; void* inet; void* ppp; void* downlink; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RFC1490_HOOK_DOWNSTREAM ; 
 int /*<<< orphan*/  NG_RFC1490_HOOK_ETHERNET ; 
 int /*<<< orphan*/  NG_RFC1490_HOOK_INET ; 
 int /*<<< orphan*/  NG_RFC1490_HOOK_PPP ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_rfc1490_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (!strcmp(name, NG_RFC1490_HOOK_DOWNSTREAM)) {
		if (priv->downlink)
			return (EISCONN);
		priv->downlink = hook;
	} else if (!strcmp(name, NG_RFC1490_HOOK_PPP)) {
		if (priv->ppp)
			return (EISCONN);
		priv->ppp = hook;
	} else if (!strcmp(name, NG_RFC1490_HOOK_INET)) {
		if (priv->inet)
			return (EISCONN);
		priv->inet = hook;
	} else if (!strcmp(name, NG_RFC1490_HOOK_ETHERNET)) {
		if (priv->ethernet)
			return (EISCONN);
		priv->ethernet = hook;
	} else
		return (EINVAL);
	return (0);
}