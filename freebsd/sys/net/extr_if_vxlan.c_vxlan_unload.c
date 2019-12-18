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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_cloner ; 
 int /*<<< orphan*/  vxlan_ifdetach_event_tag ; 
 int /*<<< orphan*/  vxlan_list_mtx ; 
 int /*<<< orphan*/  vxlan_socket_list ; 

__attribute__((used)) static void
vxlan_unload(void)
{

	EVENTHANDLER_DEREGISTER(ifnet_departure_event,
	    vxlan_ifdetach_event_tag);
	if_clone_detach(vxlan_cloner);
	mtx_destroy(&vxlan_list_mtx);
	MPASS(LIST_EMPTY(&vxlan_socket_list));
}