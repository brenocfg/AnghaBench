#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct inet6_ifaddr {TYPE_1__* idev; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  sfe_ipv6_destroy_all_rules_for_dev (struct net_device*) ; 

__attribute__((used)) static int fast_classifier_inet6_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ((struct inet6_ifaddr *)ptr)->idev->dev;

	if (dev && (event == NETDEV_DOWN)) {
		sfe_ipv6_destroy_all_rules_for_dev(dev);
	}

	return NOTIFY_DONE;
}