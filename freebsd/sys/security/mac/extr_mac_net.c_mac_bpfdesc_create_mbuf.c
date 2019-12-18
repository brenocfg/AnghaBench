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
struct bpf_d {int /*<<< orphan*/  bd_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPFD_LOCK_ASSERT (struct bpf_d*) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct bpf_d*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 int /*<<< orphan*/  bpfdesc_create_mbuf ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 

void
mac_bpfdesc_create_mbuf(struct bpf_d *d, struct mbuf *m)
{
	struct label *label;

	/* Assume reader lock is enough. */
	BPFD_LOCK_ASSERT(d);

	if (mac_policy_count == 0)
		return;

	label = mac_mbuf_to_label(m);

	MAC_POLICY_PERFORM_NOSLEEP(bpfdesc_create_mbuf, d, d->bd_label, m,
	    label);
}