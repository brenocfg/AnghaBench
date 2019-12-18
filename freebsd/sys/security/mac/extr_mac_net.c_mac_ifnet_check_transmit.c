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
struct mbuf {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  MAC_IFNET_LOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_IFNET_UNLOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  ifnet_check_transmit ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 

int
mac_ifnet_check_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct label *label;
	int error, locked;

	M_ASSERTPKTHDR(m);

	if (mac_policy_count == 0)
		return (0);

	label = mac_mbuf_to_label(m);

	MAC_IFNET_LOCK(ifp, locked);
	MAC_POLICY_CHECK_NOSLEEP(ifnet_check_transmit, ifp, ifp->if_label, m,
	    label);
	MAC_CHECK_PROBE2(ifnet_check_transmit, error, ifp, m);
	MAC_IFNET_UNLOCK(ifp, locked);

	return (error);
}