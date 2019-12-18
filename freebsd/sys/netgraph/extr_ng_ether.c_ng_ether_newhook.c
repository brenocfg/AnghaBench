#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_5__ {TYPE_1__* ifp; int /*<<< orphan*/ * upper; int /*<<< orphan*/ * orphan; int /*<<< orphan*/ * lower; } ;
struct TYPE_4__ {scalar_t__ if_hwassist; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 char* NG_ETHER_HOOK_DIVERT ; 
 char* NG_ETHER_HOOK_LOWER ; 
 char* NG_ETHER_HOOK_ORPHAN ; 
 char* NG_ETHER_HOOK_UPPER ; 
 int /*<<< orphan*/  NG_HOOK_HI_STACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_SET_RCVDATA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_SET_TO_INBOUND (int /*<<< orphan*/ *) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ether_rcv_lower ; 
 int /*<<< orphan*/  ng_ether_rcv_upper ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static	int
ng_ether_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	hook_p *hookptr;

	/* Divert hook is an alias for lower */
	if (strcmp(name, NG_ETHER_HOOK_DIVERT) == 0)
		name = NG_ETHER_HOOK_LOWER;

	/* Which hook? */
	if (strcmp(name, NG_ETHER_HOOK_UPPER) == 0) {
		hookptr = &priv->upper;
		NG_HOOK_SET_RCVDATA(hook, ng_ether_rcv_upper);
		NG_HOOK_SET_TO_INBOUND(hook);
	} else if (strcmp(name, NG_ETHER_HOOK_LOWER) == 0) {
		hookptr = &priv->lower;
		NG_HOOK_SET_RCVDATA(hook, ng_ether_rcv_lower);
	} else if (strcmp(name, NG_ETHER_HOOK_ORPHAN) == 0) {
		hookptr = &priv->orphan;
		NG_HOOK_SET_RCVDATA(hook, ng_ether_rcv_lower);
	} else
		return (EINVAL);

	/* Check if already connected (shouldn't be, but doesn't hurt) */
	if (*hookptr != NULL)
		return (EISCONN);

	/* Disable hardware checksums while 'upper' hook is connected */
	if (hookptr == &priv->upper)
		priv->ifp->if_hwassist = 0;
	NG_HOOK_HI_STACK(hook);
	/* OK */
	*hookptr = hook;
	return (0);
}