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

/* Variables and functions */
 int SCTP_MAX_VRF_ID ; 
 int /*<<< orphan*/  sctp_allocate_vrf (int) ; 
 int /*<<< orphan*/  sctp_init_ifns_for_vrf (int) ; 

void
sctp_init_vrf_list(int vrfid)
{
	if (vrfid > SCTP_MAX_VRF_ID)
		/* can't do that */
		return;

	/* Don't care about return here */
	(void)sctp_allocate_vrf(vrfid);

	/*
	 * Now we need to build all the ifn's for this vrf and there
	 * addresses
	 */
	sctp_init_ifns_for_vrf(vrfid);
}