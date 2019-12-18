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
struct notifier_block {int /*<<< orphan*/  (* notifier_call ) (struct notifier_block*,int /*<<< orphan*/ ,struct ifnet*) ;} ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int LINK_STATE_UP ; 
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  stub1 (struct notifier_block*,int /*<<< orphan*/ ,struct ifnet*) ; 
 int /*<<< orphan*/  stub2 (struct notifier_block*,int /*<<< orphan*/ ,struct ifnet*) ; 

__attribute__((used)) static void
linux_handle_ifnet_link_event(void *arg, struct ifnet *ifp, int linkstate)
{
	struct notifier_block *nb;

	nb = arg;
	if (linkstate == LINK_STATE_UP)
		nb->notifier_call(nb, NETDEV_UP, ifp);
	else
		nb->notifier_call(nb, NETDEV_DOWN, ifp);
}