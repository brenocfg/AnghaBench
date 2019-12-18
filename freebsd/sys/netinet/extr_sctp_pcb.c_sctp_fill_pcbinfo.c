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
struct sctp_pcbinfo {void* free_chunks; void* stream_oque; void* readq_count; void* chk_count; void* raddr_count; void* laddr_count; void* asoc_count; void* ep_count; } ;

/* Variables and functions */
 void* SCTP_BASE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_INP_INFO_RLOCK () ; 
 int /*<<< orphan*/  SCTP_INP_INFO_RUNLOCK () ; 
 int /*<<< orphan*/  ipi_count_asoc ; 
 int /*<<< orphan*/  ipi_count_chunk ; 
 int /*<<< orphan*/  ipi_count_ep ; 
 int /*<<< orphan*/  ipi_count_laddr ; 
 int /*<<< orphan*/  ipi_count_raddr ; 
 int /*<<< orphan*/  ipi_count_readq ; 
 int /*<<< orphan*/  ipi_count_strmoq ; 
 int /*<<< orphan*/  ipi_free_chunks ; 

void
sctp_fill_pcbinfo(struct sctp_pcbinfo *spcb)
{
	/*
	 * We really don't need to lock this, but I will just because it
	 * does not hurt.
	 */
	SCTP_INP_INFO_RLOCK();
	spcb->ep_count = SCTP_BASE_INFO(ipi_count_ep);
	spcb->asoc_count = SCTP_BASE_INFO(ipi_count_asoc);
	spcb->laddr_count = SCTP_BASE_INFO(ipi_count_laddr);
	spcb->raddr_count = SCTP_BASE_INFO(ipi_count_raddr);
	spcb->chk_count = SCTP_BASE_INFO(ipi_count_chunk);
	spcb->readq_count = SCTP_BASE_INFO(ipi_count_readq);
	spcb->stream_oque = SCTP_BASE_INFO(ipi_count_strmoq);
	spcb->free_chunks = SCTP_BASE_INFO(ipi_free_chunks);
	SCTP_INP_INFO_RUNLOCK();
}