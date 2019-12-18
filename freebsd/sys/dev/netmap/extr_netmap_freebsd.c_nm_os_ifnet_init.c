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
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_arrival_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  netmap_ifnet_arrival_handler ; 
 int /*<<< orphan*/  netmap_ifnet_departure_handler ; 
 void* nm_ifnet_ah_tag ; 
 void* nm_ifnet_dh_tag ; 

int
nm_os_ifnet_init(void)
{
	nm_ifnet_ah_tag =
		EVENTHANDLER_REGISTER(ifnet_arrival_event,
				netmap_ifnet_arrival_handler,
				NULL, EVENTHANDLER_PRI_ANY);
	nm_ifnet_dh_tag =
		EVENTHANDLER_REGISTER(ifnet_departure_event,
				netmap_ifnet_departure_handler,
				NULL, EVENTHANDLER_PRI_ANY);
	return 0;
}