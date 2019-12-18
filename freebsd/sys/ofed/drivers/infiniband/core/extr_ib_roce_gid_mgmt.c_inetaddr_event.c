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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGEADDR 131 
#define  NETDEV_CHANGEIFADDR 130 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  roce_gid_delete_all_event (struct net_device*) ; 
 int /*<<< orphan*/  roce_gid_queue_scan_event (struct net_device*) ; 

__attribute__((used)) static int
inetaddr_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *ndev = ptr;

	switch (event) {
	case NETDEV_UNREGISTER:
		roce_gid_delete_all_event(ndev);
		break;
	case NETDEV_REGISTER:
	case NETDEV_CHANGEADDR:
	case NETDEV_CHANGEIFADDR:
		roce_gid_queue_scan_event(ndev);
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}