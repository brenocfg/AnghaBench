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
typedef  int uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sctp_tcb {int /*<<< orphan*/  rport; } ;
struct sctp_queued_to_read {int sinfo_flags; int top_fsn; int fsn_included; int /*<<< orphan*/  port_from; struct sctp_tcb* stcb; struct mbuf* data; struct sctp_nets* whoFrom; int /*<<< orphan*/  reasm; void* mid; int /*<<< orphan*/  sinfo_assoc_id; void* sinfo_cumtsn; void* sinfo_tsn; void* sinfo_context; void* sinfo_ppid; int /*<<< orphan*/  sinfo_stream; } ;
struct sctp_nets {int /*<<< orphan*/  ref_count; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sctp_queued_to_read*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_alloc_a_readq (struct sctp_tcb*,struct sctp_queued_to_read*) ; 
 int /*<<< orphan*/  sctp_get_associd (struct sctp_tcb*) ; 

struct sctp_queued_to_read *
sctp_build_readq_entry(struct sctp_tcb *stcb,
    struct sctp_nets *net,
    uint32_t tsn, uint32_t ppid,
    uint32_t context, uint16_t sid,
    uint32_t mid, uint8_t flags,
    struct mbuf *dm)
{
	struct sctp_queued_to_read *read_queue_e = NULL;

	sctp_alloc_a_readq(stcb, read_queue_e);
	if (read_queue_e == NULL) {
		goto failed_build;
	}
	memset(read_queue_e, 0, sizeof(struct sctp_queued_to_read));
	read_queue_e->sinfo_stream = sid;
	read_queue_e->sinfo_flags = (flags << 8);
	read_queue_e->sinfo_ppid = ppid;
	read_queue_e->sinfo_context = context;
	read_queue_e->sinfo_tsn = tsn;
	read_queue_e->sinfo_cumtsn = tsn;
	read_queue_e->sinfo_assoc_id = sctp_get_associd(stcb);
	read_queue_e->mid = mid;
	read_queue_e->top_fsn = read_queue_e->fsn_included = 0xffffffff;
	TAILQ_INIT(&read_queue_e->reasm);
	read_queue_e->whoFrom = net;
	atomic_add_int(&net->ref_count, 1);
	read_queue_e->data = dm;
	read_queue_e->stcb = stcb;
	read_queue_e->port_from = stcb->rport;
failed_build:
	return (read_queue_e);
}