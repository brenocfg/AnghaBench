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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  if_clone_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_clone_create ; 
 int /*<<< orphan*/  vxlan_clone_destroy ; 
 int /*<<< orphan*/  vxlan_cloner ; 
 int /*<<< orphan*/  vxlan_ifdetach_event ; 
 int /*<<< orphan*/  vxlan_ifdetach_event_tag ; 
 int /*<<< orphan*/  vxlan_list_mtx ; 
 int /*<<< orphan*/  vxlan_name ; 
 int /*<<< orphan*/  vxlan_socket_list ; 

__attribute__((used)) static void
vxlan_load(void)
{

	mtx_init(&vxlan_list_mtx, "vxlan list", NULL, MTX_DEF);
	LIST_INIT(&vxlan_socket_list);
	vxlan_ifdetach_event_tag = EVENTHANDLER_REGISTER(ifnet_departure_event,
	    vxlan_ifdetach_event, NULL, EVENTHANDLER_PRI_ANY);
	vxlan_cloner = if_clone_simple(vxlan_name, vxlan_clone_create,
	    vxlan_clone_destroy, 0);
}