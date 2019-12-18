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
struct ip6q {int /*<<< orphan*/  ip6q_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ip6q*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 int /*<<< orphan*/  ip6q_reassemble ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 

void
mac_ip6q_reassemble(struct ip6q *q6, struct mbuf *m)
{
	struct label *label;

	if (mac_policy_count == 0)
		return;

	label = mac_mbuf_to_label(m);

	MAC_POLICY_PERFORM_NOSLEEP(ip6q_reassemble, q6, q6->ip6q_label, m,
	    label);
}