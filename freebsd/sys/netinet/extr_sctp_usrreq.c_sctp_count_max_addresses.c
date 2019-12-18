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
struct sctp_inpcb {int /*<<< orphan*/  def_vrf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_IPI_ADDR_RLOCK () ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_RUNLOCK () ; 
 int sctp_count_max_addresses_vrf (struct sctp_inpcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sctp_count_max_addresses(struct sctp_inpcb *inp)
{
	int cnt = 0;

	SCTP_IPI_ADDR_RLOCK();
	/* count addresses for the endpoint's default VRF */
	cnt = sctp_count_max_addresses_vrf(inp, inp->def_vrf_id);
	SCTP_IPI_ADDR_RUNLOCK();
	return (cnt);
}