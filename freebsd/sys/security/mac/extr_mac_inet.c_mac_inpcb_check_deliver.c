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
struct inpcb {int /*<<< orphan*/  inp_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct inpcb*,struct mbuf*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct inpcb*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  inpcb_check_deliver ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 

int
mac_inpcb_check_deliver(struct inpcb *inp, struct mbuf *m)
{
	struct label *label;
	int error;

	M_ASSERTPKTHDR(m);

	if (mac_policy_count == 0)
		return (0);

	label = mac_mbuf_to_label(m);

	MAC_POLICY_CHECK_NOSLEEP(inpcb_check_deliver, inp, inp->inp_label, m,
	    label);
	MAC_CHECK_PROBE2(inpcb_check_deliver, error, inp, m);

	return (error);
}