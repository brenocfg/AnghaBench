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

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 
 int /*<<< orphan*/  netinet_firewall_send ; 

void
mac_netinet_firewall_send(struct mbuf *m)
{
	struct label *label;

	M_ASSERTPKTHDR(m);

	if (mac_policy_count == 0)
		return;

	label = mac_mbuf_to_label(m);

	MAC_POLICY_PERFORM_NOSLEEP(netinet_firewall_send, m, label);
}