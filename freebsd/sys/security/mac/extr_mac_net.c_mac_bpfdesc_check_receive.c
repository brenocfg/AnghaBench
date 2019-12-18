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
struct bpf_d {int /*<<< orphan*/  bd_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPFD_LOCK_ASSERT (struct bpf_d*) ; 
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct bpf_d*,struct ifnet*) ; 
 int /*<<< orphan*/  MAC_IFNET_LOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_IFNET_UNLOCK (struct ifnet*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct bpf_d*,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpfdesc_check_receive ; 
 scalar_t__ mac_policy_count ; 

int
mac_bpfdesc_check_receive(struct bpf_d *d, struct ifnet *ifp)
{
	int error, locked;

	/* Assume reader lock is enough. */
	BPFD_LOCK_ASSERT(d);

	if (mac_policy_count == 0)
		return (0);

	MAC_IFNET_LOCK(ifp, locked);
	MAC_POLICY_CHECK_NOSLEEP(bpfdesc_check_receive, d, d->bd_label, ifp,
	    ifp->if_label);
	MAC_CHECK_PROBE2(bpfdesc_check_receive, error, d, ifp);
	MAC_IFNET_UNLOCK(ifp, locked);

	return (error);
}