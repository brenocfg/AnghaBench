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
struct sockaddr_storage {int dummy; } ;
struct sctp_tcb {int dummy; } ;
struct sctp_inpcb {int /*<<< orphan*/  def_vrf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_IPI_ADDR_RLOCK () ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_RUNLOCK () ; 
 size_t sctp_fill_up_addresses_vrf (struct sctp_inpcb*,struct sctp_tcb*,size_t,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
sctp_fill_up_addresses(struct sctp_inpcb *inp,
    struct sctp_tcb *stcb,
    size_t limit,
    struct sockaddr_storage *sas)
{
	size_t size = 0;

	SCTP_IPI_ADDR_RLOCK();
	/* fill up addresses for the endpoint's default vrf */
	size = sctp_fill_up_addresses_vrf(inp, stcb, limit, sas,
	    inp->def_vrf_id);
	SCTP_IPI_ADDR_RUNLOCK();
	return (size);
}