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
struct ifnet {int /*<<< orphan*/  if_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_IFNET_LOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_IFNET_UNLOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_create ; 
 scalar_t__ mac_policy_count ; 

void
mac_ifnet_create(struct ifnet *ifp)
{
	int locked;

	if (mac_policy_count == 0)
		return;

	MAC_IFNET_LOCK(ifp, locked);
	MAC_POLICY_PERFORM_NOSLEEP(ifnet_create, ifp, ifp->if_label);
	MAC_IFNET_UNLOCK(ifp, locked);
}