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
struct sctp_iterator {int pcb_flags; int pcb_features; int iterator_flags; int done_current_ep; int (* function_inp ) (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* function_inp_end ) (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int asoc_state; scalar_t__ no_chunk_output; struct sctp_inpcb* inp; int /*<<< orphan*/  val; int /*<<< orphan*/  pointer; struct sctp_inpcb* stcb; int /*<<< orphan*/  (* function_assoc ) (struct sctp_inpcb*,struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* function_atend ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int state; int /*<<< orphan*/  refcnt; } ;
struct sctp_inpcb {int sctp_flags; int sctp_features; TYPE_1__ asoc; int /*<<< orphan*/  sctp_asoc_list; } ;
struct TYPE_4__ {int iterator_flags; struct sctp_iterator* cur_it; } ;

/* Variables and functions */
 struct sctp_inpcb* LIST_FIRST (int /*<<< orphan*/ *) ; 
 void* LIST_NEXT (struct sctp_inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_FREE (struct sctp_iterator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_INP_DECR_REF (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_INCR_REF (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_INFO_RLOCK () ; 
 int /*<<< orphan*/  SCTP_INP_INFO_RUNLOCK () ; 
 int /*<<< orphan*/  SCTP_INP_RLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_RUNLOCK (struct sctp_inpcb*) ; 
 int SCTP_ITERATOR_DO_SINGLE_INP ; 
 int /*<<< orphan*/  SCTP_ITERATOR_LOCK () ; 
 int SCTP_ITERATOR_MAX_AT_ONCE ; 
 int SCTP_ITERATOR_STOP_CUR_INP ; 
 int SCTP_ITERATOR_STOP_CUR_IT ; 
 int /*<<< orphan*/  SCTP_ITERATOR_UNLOCK () ; 
 int /*<<< orphan*/  SCTP_M_ITER ; 
 int /*<<< orphan*/  SCTP_OUTPUT_FROM_T3 ; 
 int /*<<< orphan*/  SCTP_PRINTF (char*,int) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_chunk_output (struct sctp_inpcb*,struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ sctp_it_ctl ; 
 int /*<<< orphan*/  sctp_list ; 
 int /*<<< orphan*/  sctp_tcblist ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct sctp_inpcb*,struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub5 (struct sctp_inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sctp_iterator_work(struct sctp_iterator *it)
{
	int iteration_count = 0;
	int inp_skip = 0;
	int first_in = 1;
	struct sctp_inpcb *tinp;

	SCTP_INP_INFO_RLOCK();
	SCTP_ITERATOR_LOCK();
	sctp_it_ctl.cur_it = it;
	if (it->inp) {
		SCTP_INP_RLOCK(it->inp);
		SCTP_INP_DECR_REF(it->inp);
	}
	if (it->inp == NULL) {
		/* iterator is complete */
done_with_iterator:
		sctp_it_ctl.cur_it = NULL;
		SCTP_ITERATOR_UNLOCK();
		SCTP_INP_INFO_RUNLOCK();
		if (it->function_atend != NULL) {
			(*it->function_atend) (it->pointer, it->val);
		}
		SCTP_FREE(it, SCTP_M_ITER);
		return;
	}
select_a_new_ep:
	if (first_in) {
		first_in = 0;
	} else {
		SCTP_INP_RLOCK(it->inp);
	}
	while (((it->pcb_flags) &&
	    ((it->inp->sctp_flags & it->pcb_flags) != it->pcb_flags)) ||
	    ((it->pcb_features) &&
	    ((it->inp->sctp_features & it->pcb_features) != it->pcb_features))) {
		/* endpoint flags or features don't match, so keep looking */
		if (it->iterator_flags & SCTP_ITERATOR_DO_SINGLE_INP) {
			SCTP_INP_RUNLOCK(it->inp);
			goto done_with_iterator;
		}
		tinp = it->inp;
		it->inp = LIST_NEXT(it->inp, sctp_list);
		SCTP_INP_RUNLOCK(tinp);
		if (it->inp == NULL) {
			goto done_with_iterator;
		}
		SCTP_INP_RLOCK(it->inp);
	}
	/* now go through each assoc which is in the desired state */
	if (it->done_current_ep == 0) {
		if (it->function_inp != NULL)
			inp_skip = (*it->function_inp) (it->inp, it->pointer, it->val);
		it->done_current_ep = 1;
	}
	if (it->stcb == NULL) {
		/* run the per instance function */
		it->stcb = LIST_FIRST(&it->inp->sctp_asoc_list);
	}
	if ((inp_skip) || it->stcb == NULL) {
		if (it->function_inp_end != NULL) {
			inp_skip = (*it->function_inp_end) (it->inp,
			    it->pointer,
			    it->val);
		}
		SCTP_INP_RUNLOCK(it->inp);
		goto no_stcb;
	}
	while (it->stcb) {
		SCTP_TCB_LOCK(it->stcb);
		if (it->asoc_state && ((it->stcb->asoc.state & it->asoc_state) != it->asoc_state)) {
			/* not in the right state... keep looking */
			SCTP_TCB_UNLOCK(it->stcb);
			goto next_assoc;
		}
		/* see if we have limited out the iterator loop */
		iteration_count++;
		if (iteration_count > SCTP_ITERATOR_MAX_AT_ONCE) {
			/* Pause to let others grab the lock */
			atomic_add_int(&it->stcb->asoc.refcnt, 1);
			SCTP_TCB_UNLOCK(it->stcb);
			SCTP_INP_INCR_REF(it->inp);
			SCTP_INP_RUNLOCK(it->inp);
			SCTP_ITERATOR_UNLOCK();
			SCTP_INP_INFO_RUNLOCK();
			SCTP_INP_INFO_RLOCK();
			SCTP_ITERATOR_LOCK();
			if (sctp_it_ctl.iterator_flags) {
				/* We won't be staying here */
				SCTP_INP_DECR_REF(it->inp);
				atomic_add_int(&it->stcb->asoc.refcnt, -1);
				if (sctp_it_ctl.iterator_flags &
				    SCTP_ITERATOR_STOP_CUR_IT) {
					sctp_it_ctl.iterator_flags &= ~SCTP_ITERATOR_STOP_CUR_IT;
					goto done_with_iterator;
				}
				if (sctp_it_ctl.iterator_flags &
				    SCTP_ITERATOR_STOP_CUR_INP) {
					sctp_it_ctl.iterator_flags &= ~SCTP_ITERATOR_STOP_CUR_INP;
					goto no_stcb;
				}
				/* If we reach here huh? */
				SCTP_PRINTF("Unknown it ctl flag %x\n",
				    sctp_it_ctl.iterator_flags);
				sctp_it_ctl.iterator_flags = 0;
			}
			SCTP_INP_RLOCK(it->inp);
			SCTP_INP_DECR_REF(it->inp);
			SCTP_TCB_LOCK(it->stcb);
			atomic_add_int(&it->stcb->asoc.refcnt, -1);
			iteration_count = 0;
		}

		/* run function on this one */
		(*it->function_assoc) (it->inp, it->stcb, it->pointer, it->val);

		/*
		 * we lie here, it really needs to have its own type but
		 * first I must verify that this won't effect things :-0
		 */
		if (it->no_chunk_output == 0)
			sctp_chunk_output(it->inp, it->stcb, SCTP_OUTPUT_FROM_T3, SCTP_SO_NOT_LOCKED);

		SCTP_TCB_UNLOCK(it->stcb);
next_assoc:
		it->stcb = LIST_NEXT(it->stcb, sctp_tcblist);
		if (it->stcb == NULL) {
			/* Run last function */
			if (it->function_inp_end != NULL) {
				inp_skip = (*it->function_inp_end) (it->inp,
				    it->pointer,
				    it->val);
			}
		}
	}
	SCTP_INP_RUNLOCK(it->inp);
no_stcb:
	/* done with all assocs on this endpoint, move on to next endpoint */
	it->done_current_ep = 0;
	if (it->iterator_flags & SCTP_ITERATOR_DO_SINGLE_INP) {
		it->inp = NULL;
	} else {
		it->inp = LIST_NEXT(it->inp, sctp_list);
	}
	if (it->inp == NULL) {
		goto done_with_iterator;
	}
	goto select_a_new_ep;
}