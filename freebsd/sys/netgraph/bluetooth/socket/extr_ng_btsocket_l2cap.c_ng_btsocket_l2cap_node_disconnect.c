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
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/ * NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_UNREF (int /*<<< orphan*/ ) ; 
 int ng_btsocket_l2cap_wakeup_route_task () ; 

__attribute__((used)) static int
ng_btsocket_l2cap_node_disconnect(hook_p hook)
{
	/*
	 * If hook has private information than we must have this hook in
	 * the routing table and must schedule cleaning for the routing table.
	 * Otherwise hook was connected but we never got "hook_info" message,
	 * so we have never added this hook to the routing table and it save
	 * to just delete it.
	 */

	if (NG_HOOK_PRIVATE(hook) != NULL)
		return (ng_btsocket_l2cap_wakeup_route_task());

	NG_HOOK_UNREF(hook); /* Remove extra reference */

	return (0);
}