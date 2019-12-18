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
typedef  scalar_t__ uint32_t ;
struct sctp_tcb {TYPE_2__* sctp_socket; TYPE_1__* sctp_ep; } ;
struct sctp_stream_in {scalar_t__ pd_api_started; scalar_t__ last_mid_delivered; int /*<<< orphan*/  inqueue; int /*<<< orphan*/  uno_inqueue; } ;
struct sctp_queued_to_read {scalar_t__ end_added; scalar_t__ mid; scalar_t__ on_strm_q; scalar_t__ on_read_q; scalar_t__ length; int pdapi_started; int sinfo_flags; scalar_t__ last_frag_seen; int /*<<< orphan*/  sinfo_tsn; scalar_t__ first_frag_seen; int /*<<< orphan*/  fsn_included; int /*<<< orphan*/  top_fsn; } ;
struct sctp_association {scalar_t__ idata_supported; scalar_t__ size_on_all_streams; int /*<<< orphan*/  cnt_on_all_streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_rcv; } ;
struct TYPE_3__ {scalar_t__ partial_delivery_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,struct sctp_queued_to_read*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int SCTP_DATA_NOT_FRAG ; 
 int /*<<< orphan*/  SCTP_DEBUG_XXX ; 
 scalar_t__ SCTP_MID_EQ (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SCTP_ON_ORDERED ; 
 scalar_t__ SCTP_ON_UNORDERED ; 
 int SCTP_PARTIAL_DELIVERY_SHIFT ; 
 int SCTP_SB_LIMIT_RCV (TYPE_2__*) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_STAT_INCR_COUNTER64 (int /*<<< orphan*/ ) ; 
 struct sctp_queued_to_read* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct sctp_queued_to_read* TAILQ_NEXT (struct sctp_queued_to_read*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_queued_to_read*,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,scalar_t__) ; 
 int /*<<< orphan*/  next_instrm ; 
 int /*<<< orphan*/  panic (char*,struct sctp_queued_to_read*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_add_to_readq (TYPE_1__*,struct sctp_tcb*,struct sctp_queued_to_read*,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_handle_old_unordered_data (struct sctp_tcb*,struct sctp_association*,struct sctp_stream_in*,struct sctp_queued_to_read*,scalar_t__,int) ; 
 int /*<<< orphan*/  sctp_mark_non_revokable (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ucount_decr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctps_reasmusrmsgs ; 

__attribute__((used)) static int
sctp_deliver_reasm_check(struct sctp_tcb *stcb, struct sctp_association *asoc,
    struct sctp_stream_in *strm, int inp_read_lock_held)
{
	/*
	 * Given a stream, strm, see if any of the SSN's on it that are
	 * fragmented are ready to deliver. If so go ahead and place them on
	 * the read queue. In so placing if we have hit the end, then we
	 * need to remove them from the stream's queue.
	 */
	struct sctp_queued_to_read *control, *nctl = NULL;
	uint32_t next_to_del;
	uint32_t pd_point;
	int ret = 0;

	if (stcb->sctp_socket) {
		pd_point = min(SCTP_SB_LIMIT_RCV(stcb->sctp_socket) >> SCTP_PARTIAL_DELIVERY_SHIFT,
		    stcb->sctp_ep->partial_delivery_point);
	} else {
		pd_point = stcb->sctp_ep->partial_delivery_point;
	}
	control = TAILQ_FIRST(&strm->uno_inqueue);

	if ((control != NULL) &&
	    (asoc->idata_supported == 0)) {
		/* Special handling needed for "old" data format */
		if (sctp_handle_old_unordered_data(stcb, asoc, strm, control, pd_point, inp_read_lock_held)) {
			goto done_un;
		}
	}
	if (strm->pd_api_started) {
		/* Can't add more */
		return (0);
	}
	while (control) {
		SCTPDBG(SCTP_DEBUG_XXX, "Looking at control: %p e(%d) ssn: %u top_fsn: %u inc_fsn: %u -uo\n",
		    control, control->end_added, control->mid, control->top_fsn, control->fsn_included);
		nctl = TAILQ_NEXT(control, next_instrm);
		if (control->end_added) {
			/* We just put the last bit on */
			if (control->on_strm_q) {
#ifdef INVARIANTS
				if (control->on_strm_q != SCTP_ON_UNORDERED) {
					panic("Huh control: %p on_q: %d -- not unordered?",
					    control, control->on_strm_q);
				}
#endif
				SCTP_STAT_INCR_COUNTER64(sctps_reasmusrmsgs);
				TAILQ_REMOVE(&strm->uno_inqueue, control, next_instrm);
				control->on_strm_q = 0;
			}
			if (control->on_read_q == 0) {
				sctp_add_to_readq(stcb->sctp_ep, stcb,
				    control,
				    &stcb->sctp_socket->so_rcv, control->end_added,
				    inp_read_lock_held, SCTP_SO_NOT_LOCKED);
			}
		} else {
			/* Can we do a PD-API for this un-ordered guy? */
			if ((control->length >= pd_point) && (strm->pd_api_started == 0)) {
				strm->pd_api_started = 1;
				control->pdapi_started = 1;
				sctp_add_to_readq(stcb->sctp_ep, stcb,
				    control,
				    &stcb->sctp_socket->so_rcv, control->end_added,
				    inp_read_lock_held, SCTP_SO_NOT_LOCKED);

				break;
			}
		}
		control = nctl;
	}
done_un:
	control = TAILQ_FIRST(&strm->inqueue);
	if (strm->pd_api_started) {
		/* Can't add more */
		return (0);
	}
	if (control == NULL) {
		return (ret);
	}
	if (SCTP_MID_EQ(asoc->idata_supported, strm->last_mid_delivered, control->mid)) {
		/*
		 * Ok the guy at the top was being partially delivered
		 * completed, so we remove it. Note the pd_api flag was
		 * taken off when the chunk was merged on in
		 * sctp_queue_data_for_reasm below.
		 */
		nctl = TAILQ_NEXT(control, next_instrm);
		SCTPDBG(SCTP_DEBUG_XXX,
		    "Looking at control: %p e(%d) ssn: %u top_fsn: %u inc_fsn: %u (lastdel: %u)- o\n",
		    control, control->end_added, control->mid,
		    control->top_fsn, control->fsn_included,
		    strm->last_mid_delivered);
		if (control->end_added) {
			if (control->on_strm_q) {
#ifdef INVARIANTS
				if (control->on_strm_q != SCTP_ON_ORDERED) {
					panic("Huh control: %p on_q: %d -- not ordered?",
					    control, control->on_strm_q);
				}
#endif
				SCTP_STAT_INCR_COUNTER64(sctps_reasmusrmsgs);
				TAILQ_REMOVE(&strm->inqueue, control, next_instrm);
				if (asoc->size_on_all_streams >= control->length) {
					asoc->size_on_all_streams -= control->length;
				} else {
#ifdef INVARIANTS
					panic("size_on_all_streams = %u smaller than control length %u", asoc->size_on_all_streams, control->length);
#else
					asoc->size_on_all_streams = 0;
#endif
				}
				sctp_ucount_decr(asoc->cnt_on_all_streams);
				control->on_strm_q = 0;
			}
			if (strm->pd_api_started && control->pdapi_started) {
				control->pdapi_started = 0;
				strm->pd_api_started = 0;
			}
			if (control->on_read_q == 0) {
				sctp_add_to_readq(stcb->sctp_ep, stcb,
				    control,
				    &stcb->sctp_socket->so_rcv, control->end_added,
				    inp_read_lock_held, SCTP_SO_NOT_LOCKED);
			}
			control = nctl;
		}
	}
	if (strm->pd_api_started) {
		/*
		 * Can't add more must have gotten an un-ordered above being
		 * partially delivered.
		 */
		return (0);
	}
deliver_more:
	next_to_del = strm->last_mid_delivered + 1;
	if (control) {
		SCTPDBG(SCTP_DEBUG_XXX,
		    "Looking at control: %p e(%d) ssn: %u top_fsn: %u inc_fsn: %u (nxtdel: %u)- o\n",
		    control, control->end_added, control->mid, control->top_fsn, control->fsn_included,
		    next_to_del);
		nctl = TAILQ_NEXT(control, next_instrm);
		if (SCTP_MID_EQ(asoc->idata_supported, control->mid, next_to_del) &&
		    (control->first_frag_seen)) {
			int done;

			/* Ok we can deliver it onto the stream. */
			if (control->end_added) {
				/* We are done with it afterwards */
				if (control->on_strm_q) {
#ifdef INVARIANTS
					if (control->on_strm_q != SCTP_ON_ORDERED) {
						panic("Huh control: %p on_q: %d -- not ordered?",
						    control, control->on_strm_q);
					}
#endif
					SCTP_STAT_INCR_COUNTER64(sctps_reasmusrmsgs);
					TAILQ_REMOVE(&strm->inqueue, control, next_instrm);
					if (asoc->size_on_all_streams >= control->length) {
						asoc->size_on_all_streams -= control->length;
					} else {
#ifdef INVARIANTS
						panic("size_on_all_streams = %u smaller than control length %u", asoc->size_on_all_streams, control->length);
#else
						asoc->size_on_all_streams = 0;
#endif
					}
					sctp_ucount_decr(asoc->cnt_on_all_streams);
					control->on_strm_q = 0;
				}
				ret++;
			}
			if (((control->sinfo_flags >> 8) & SCTP_DATA_NOT_FRAG) == SCTP_DATA_NOT_FRAG) {
				/*
				 * A singleton now slipping through - mark
				 * it non-revokable too
				 */
				sctp_mark_non_revokable(asoc, control->sinfo_tsn);
			} else if (control->end_added == 0) {
				/*
				 * Check if we can defer adding until its
				 * all there
				 */
				if ((control->length < pd_point) || (strm->pd_api_started)) {
					/*
					 * Don't need it or cannot add more
					 * (one being delivered that way)
					 */
					goto out;
				}
			}
			done = (control->end_added) && (control->last_frag_seen);
			if (control->on_read_q == 0) {
				if (!done) {
					if (asoc->size_on_all_streams >= control->length) {
						asoc->size_on_all_streams -= control->length;
					} else {
#ifdef INVARIANTS
						panic("size_on_all_streams = %u smaller than control length %u", asoc->size_on_all_streams, control->length);
#else
						asoc->size_on_all_streams = 0;
#endif
					}
					strm->pd_api_started = 1;
					control->pdapi_started = 1;
				}
				sctp_add_to_readq(stcb->sctp_ep, stcb,
				    control,
				    &stcb->sctp_socket->so_rcv, control->end_added,
				    inp_read_lock_held, SCTP_SO_NOT_LOCKED);
			}
			strm->last_mid_delivered = next_to_del;
			if (done) {
				control = nctl;
				goto deliver_more;
			}
		}
	}
out:
	return (ret);
}