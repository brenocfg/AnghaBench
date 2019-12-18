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
 int /*<<< orphan*/  NETDEV_CHANGEIFADDR ; 
 int /*<<< orphan*/  stub1 (struct notifier_block*,int /*<<< orphan*/ ,struct ifnet*) ; 

__attribute__((used)) static void
linux_handle_ifaddr_event(void *arg, struct ifnet *ifp)
{
	struct notifier_block *nb;

	nb = arg;
	nb->notifier_call(nb, NETDEV_CHANGEIFADDR, ifp);
}