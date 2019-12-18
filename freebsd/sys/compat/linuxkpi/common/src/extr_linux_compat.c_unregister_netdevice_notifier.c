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
struct notifier_block {int /*<<< orphan*/ * tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t NETDEV_CHANGEADDR ; 
 size_t NETDEV_REGISTER ; 
 size_t NETDEV_UNREGISTER ; 
 size_t NETDEV_UP ; 
 int /*<<< orphan*/  iflladdr_event ; 
 int /*<<< orphan*/  ifnet_arrival_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  ifnet_link_event ; 

int
unregister_netdevice_notifier(struct notifier_block *nb)
{

	EVENTHANDLER_DEREGISTER(ifnet_link_event,
	    nb->tags[NETDEV_UP]);
	EVENTHANDLER_DEREGISTER(ifnet_arrival_event,
	    nb->tags[NETDEV_REGISTER]);
	EVENTHANDLER_DEREGISTER(ifnet_departure_event,
	    nb->tags[NETDEV_UNREGISTER]);
	EVENTHANDLER_DEREGISTER(iflladdr_event,
	    nb->tags[NETDEV_CHANGEADDR]);

	return (0);
}