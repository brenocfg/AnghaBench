#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ can_take_data; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ chunk_id; } ;
struct sctp_tmit_chunk {int send_size; TYPE_3__* asoc; struct sctp_nets* whoTo; scalar_t__ snd_count; int /*<<< orphan*/  sent; struct mbuf* data; int /*<<< orphan*/  flags; TYPE_2__ rec; scalar_t__ copy_by_ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl_queue_cnt; int /*<<< orphan*/  asconf_send_queue; } ;
struct sctp_tcb {TYPE_3__ asoc; int /*<<< orphan*/  sctp_ep; } ;
struct sctp_nets {int /*<<< orphan*/  ref_count; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_FLAGS_FRAGMENT_OK ; 
 int /*<<< orphan*/  SCTP_ASCONF ; 
 int /*<<< orphan*/  SCTP_DATAGRAM_UNSENT ; 
 int /*<<< orphan*/  SCTP_PCB_FLAGS_MULTIPLE_ASCONFS ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK_ASSERT (struct sctp_tcb*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sctp_tmit_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_alloc_a_chunk (struct sctp_tcb*,struct sctp_tmit_chunk*) ; 
 struct mbuf* sctp_compose_asconf (struct sctp_tcb*,int*,int) ; 
 int /*<<< orphan*/  sctp_is_feature_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  sctp_next ; 

void
sctp_send_asconf(struct sctp_tcb *stcb, struct sctp_nets *net, int addr_locked)
{
	/*
	 * formulate and queue an ASCONF to the peer. ASCONF parameters
	 * should be queued on the assoc queue.
	 */
	struct sctp_tmit_chunk *chk;
	struct mbuf *m_asconf;
	int len;

	SCTP_TCB_LOCK_ASSERT(stcb);

	if ((!TAILQ_EMPTY(&stcb->asoc.asconf_send_queue)) &&
	    (!sctp_is_feature_on(stcb->sctp_ep, SCTP_PCB_FLAGS_MULTIPLE_ASCONFS))) {
		/* can't send a new one if there is one in flight already */
		return;
	}

	/* compose an ASCONF chunk, maximum length is PMTU */
	m_asconf = sctp_compose_asconf(stcb, &len, addr_locked);
	if (m_asconf == NULL) {
		return;
	}

	sctp_alloc_a_chunk(stcb, chk);
	if (chk == NULL) {
		/* no memory */
		sctp_m_freem(m_asconf);
		return;
	}

	chk->copy_by_ref = 0;
	chk->rec.chunk_id.id = SCTP_ASCONF;
	chk->rec.chunk_id.can_take_data = 0;
	chk->flags = CHUNK_FLAGS_FRAGMENT_OK;
	chk->data = m_asconf;
	chk->send_size = len;
	chk->sent = SCTP_DATAGRAM_UNSENT;
	chk->snd_count = 0;
	chk->asoc = &stcb->asoc;
	chk->whoTo = net;
	if (chk->whoTo) {
		atomic_add_int(&chk->whoTo->ref_count, 1);
	}
	TAILQ_INSERT_TAIL(&chk->asoc->asconf_send_queue, chk, sctp_next);
	chk->asoc->ctrl_queue_cnt++;
	return;
}