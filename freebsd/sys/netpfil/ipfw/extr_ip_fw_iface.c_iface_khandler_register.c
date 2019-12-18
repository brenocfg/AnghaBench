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
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_arrival_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 void* ipfw_ifattach_event ; 
 void* ipfw_ifdetach_event ; 
 int /*<<< orphan*/  ipfw_kifhandler ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ num_vnets ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vnet_mtx ; 

__attribute__((used)) static void
iface_khandler_register()
{
	int create;

	create = 0;

	mtx_lock(&vnet_mtx);
	if (num_vnets == 0)
		create = 1;
	num_vnets++;
	mtx_unlock(&vnet_mtx);

	if (create == 0)
		return;

	printf("IPFW: starting up interface tracker\n");

	ipfw_ifdetach_event = EVENTHANDLER_REGISTER(
	    ifnet_departure_event, ipfw_kifhandler, NULL,
	    EVENTHANDLER_PRI_ANY);
	ipfw_ifattach_event = EVENTHANDLER_REGISTER(
	    ifnet_arrival_event, ipfw_kifhandler, (void*)((uintptr_t)1),
	    EVENTHANDLER_PRI_ANY);
}