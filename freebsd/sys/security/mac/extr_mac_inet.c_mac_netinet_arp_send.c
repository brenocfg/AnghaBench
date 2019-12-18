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
 int /*<<< orphan*/  MAC_IFNET_LOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_IFNET_UNLOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 
 int /*<<< orphan*/  netinet_arp_send ; 

void
mac_netinet_arp_send(struct ifnet *ifp, struct mbuf *m)
{
	struct label *mlabel;
	int locked;

	if (mac_policy_count == 0)
		return;

	mlabel = mac_mbuf_to_label(m);

	MAC_IFNET_LOCK(ifp, locked);
	MAC_POLICY_PERFORM_NOSLEEP(netinet_arp_send, ifp, ifp->if_label, m,
	    mlabel);
	MAC_IFNET_UNLOCK(ifp, locked);
}