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
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct notifier_block*,int /*<<< orphan*/ ) ; 
 size_t NETDEV_CHANGEIFADDR ; 
 int /*<<< orphan*/  ifaddr_event ; 
 int /*<<< orphan*/  linux_handle_ifaddr_event ; 

int
register_inetaddr_notifier(struct notifier_block *nb)
{

	nb->tags[NETDEV_CHANGEIFADDR] = EVENTHANDLER_REGISTER(
	    ifaddr_event, linux_handle_ifaddr_event, nb, 0);
	return (0);
}