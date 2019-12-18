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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int IFNET_EVENT_PCP ; 
 scalar_t__ is_vlan_dev (struct ifnet*) ; 
 int /*<<< orphan*/  roce_gid_delete_all_event (struct ifnet*) ; 
 int /*<<< orphan*/  roce_gid_queue_scan_event (struct ifnet*) ; 

__attribute__((used)) static void
roce_ifnet_event(void *arg, struct ifnet *ifp, int event)
{
	if (event != IFNET_EVENT_PCP || is_vlan_dev(ifp))
		return;

	/* make sure GID table is reloaded */
	roce_gid_delete_all_event(ifp);
	roce_gid_queue_scan_event(ifp);
}