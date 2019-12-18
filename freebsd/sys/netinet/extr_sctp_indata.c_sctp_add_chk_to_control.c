#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int rcv_flags; int /*<<< orphan*/  ppid; int /*<<< orphan*/  tsn; int /*<<< orphan*/  fsn; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct sctp_tmit_chunk {TYPE_2__ rec; int /*<<< orphan*/ * data; scalar_t__ send_size; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; } ;
struct sctp_stream_in {int /*<<< orphan*/  inqueue; int /*<<< orphan*/  uno_inqueue; scalar_t__ pd_api_started; } ;
struct sctp_queued_to_read {int first_frag_seen; scalar_t__ on_strm_q; int end_added; int last_frag_seen; scalar_t__ pdapi_started; scalar_t__ on_read_q; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_tsn; int /*<<< orphan*/  fsn_included; int /*<<< orphan*/ * data; } ;
struct sctp_association {int /*<<< orphan*/  cnt_on_all_streams; int /*<<< orphan*/  cnt_on_reasm_queue; int /*<<< orphan*/  size_on_reasm_queue; } ;

/* Variables and functions */
 int SCTP_DATA_FIRST_FRAG ; 
 int SCTP_DATA_LAST_FRAG ; 
 int /*<<< orphan*/  SCTP_INP_READ_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_INP_READ_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_ON_ORDERED ; 
 scalar_t__ SCTP_ON_UNORDERED ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_queued_to_read*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_instrm ; 
 int /*<<< orphan*/  panic (char*,struct sctp_queued_to_read*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_add_to_tail_pointer (struct sctp_queued_to_read*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_free_a_chunk (struct sctp_tcb*,struct sctp_tmit_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_mark_non_revokable (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_setup_tail_pointer (struct sctp_queued_to_read*) ; 
 int /*<<< orphan*/  sctp_ucount_decr (int /*<<< orphan*/ ) ; 

uint32_t
sctp_add_chk_to_control(struct sctp_queued_to_read *control,
    struct sctp_stream_in *strm,
    struct sctp_tcb *stcb, struct sctp_association *asoc,
    struct sctp_tmit_chunk *chk, int hold_rlock)
{
	/*
	 * Given a control and a chunk, merge the data from the chk onto the
	 * control and free up the chunk resources.
	 */
	uint32_t added = 0;
	int i_locked = 0;

	if (control->on_read_q && (hold_rlock == 0)) {
		/*
		 * Its being pd-api'd so we must do some locks.
		 */
		SCTP_INP_READ_LOCK(stcb->sctp_ep);
		i_locked = 1;
	}
	if (control->data == NULL) {
		control->data = chk->data;
		sctp_setup_tail_pointer(control);
	} else {
		sctp_add_to_tail_pointer(control, chk->data, &added);
	}
	control->fsn_included = chk->rec.data.fsn;
	asoc->size_on_reasm_queue -= chk->send_size;
	sctp_ucount_decr(asoc->cnt_on_reasm_queue);
	sctp_mark_non_revokable(asoc, chk->rec.data.tsn);
	chk->data = NULL;
	if (chk->rec.data.rcv_flags & SCTP_DATA_FIRST_FRAG) {
		control->first_frag_seen = 1;
		control->sinfo_tsn = chk->rec.data.tsn;
		control->sinfo_ppid = chk->rec.data.ppid;
	}
	if (chk->rec.data.rcv_flags & SCTP_DATA_LAST_FRAG) {
		/* Its complete */
		if ((control->on_strm_q) && (control->on_read_q)) {
			if (control->pdapi_started) {
				control->pdapi_started = 0;
				strm->pd_api_started = 0;
			}
			if (control->on_strm_q == SCTP_ON_UNORDERED) {
				/* Unordered */
				TAILQ_REMOVE(&strm->uno_inqueue, control, next_instrm);
				control->on_strm_q = 0;
			} else if (control->on_strm_q == SCTP_ON_ORDERED) {
				/* Ordered */
				TAILQ_REMOVE(&strm->inqueue, control, next_instrm);
				/*
				 * Don't need to decrement
				 * size_on_all_streams, since control is on
				 * the read queue.
				 */
				sctp_ucount_decr(asoc->cnt_on_all_streams);
				control->on_strm_q = 0;
#ifdef INVARIANTS
			} else if (control->on_strm_q) {
				panic("Unknown state on ctrl: %p on_strm_q: %d", control,
				    control->on_strm_q);
#endif
			}
		}
		control->end_added = 1;
		control->last_frag_seen = 1;
	}
	if (i_locked) {
		SCTP_INP_READ_UNLOCK(stcb->sctp_ep);
	}
	sctp_free_a_chunk(stcb, chk, SCTP_SO_NOT_LOCKED);
	return (added);
}