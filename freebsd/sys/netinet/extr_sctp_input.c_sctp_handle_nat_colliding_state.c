#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct sctpasochead {int dummy; } ;
struct TYPE_4__ {void* my_vtag; int /*<<< orphan*/  refcnt; } ;
struct sctp_tcb {TYPE_2__* sctp_ep; TYPE_1__ asoc; int /*<<< orphan*/  rport; } ;
struct TYPE_5__ {int /*<<< orphan*/  sctp_lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct sctpasochead*,struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 struct sctpasochead* SCTP_BASE_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_INP_INFO_WLOCK () ; 
 int /*<<< orphan*/  SCTP_INP_INFO_WUNLOCK () ; 
 size_t SCTP_PCBHASH_ASOC (void*,struct sctpasochead*) ; 
 int /*<<< orphan*/  SCTP_SET_STATE (struct sctp_tcb*,scalar_t__) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 scalar_t__ SCTP_STATE_COOKIE_ECHOED ; 
 scalar_t__ SCTP_STATE_COOKIE_WAIT ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hashasocmark ; 
 int /*<<< orphan*/  sctp_asochash ; 
 int /*<<< orphan*/  sctp_asocs ; 
 void* sctp_select_a_tag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_send_initiate (TYPE_2__*,struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_stop_all_cookie_timers (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_toss_old_cookies (struct sctp_tcb*,TYPE_1__*) ; 

__attribute__((used)) static int
sctp_handle_nat_colliding_state(struct sctp_tcb *stcb)
{
	/*
	 * Return 0 means we want you to proceed with the abort non-zero
	 * means no abort processing.
	 */
	uint32_t new_vtag;
	struct sctpasochead *head;

	if ((SCTP_GET_STATE(stcb) == SCTP_STATE_COOKIE_WAIT) ||
	    (SCTP_GET_STATE(stcb) == SCTP_STATE_COOKIE_ECHOED)) {
		new_vtag = sctp_select_a_tag(stcb->sctp_ep, stcb->sctp_ep->sctp_lport, stcb->rport, 1);
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_INP_INFO_WLOCK();
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
	} else {
		return (0);
	}
	if (SCTP_GET_STATE(stcb) == SCTP_STATE_COOKIE_WAIT) {
		/* generate a new vtag and send init */
		LIST_REMOVE(stcb, sctp_asocs);
		stcb->asoc.my_vtag = new_vtag;
		head = &SCTP_BASE_INFO(sctp_asochash)[SCTP_PCBHASH_ASOC(stcb->asoc.my_vtag, SCTP_BASE_INFO(hashasocmark))];
		/*
		 * put it in the bucket in the vtag hash of assoc's for the
		 * system
		 */
		LIST_INSERT_HEAD(head, stcb, sctp_asocs);
		SCTP_INP_INFO_WUNLOCK();
		sctp_send_initiate(stcb->sctp_ep, stcb, SCTP_SO_NOT_LOCKED);
		return (1);
	} else {
		/*
		 * treat like a case where the cookie expired i.e.: - dump
		 * current cookie. - generate a new vtag. - resend init.
		 */
		/* generate a new vtag and send init */
		LIST_REMOVE(stcb, sctp_asocs);
		SCTP_SET_STATE(stcb, SCTP_STATE_COOKIE_WAIT);
		sctp_stop_all_cookie_timers(stcb);
		sctp_toss_old_cookies(stcb, &stcb->asoc);
		stcb->asoc.my_vtag = new_vtag;
		head = &SCTP_BASE_INFO(sctp_asochash)[SCTP_PCBHASH_ASOC(stcb->asoc.my_vtag, SCTP_BASE_INFO(hashasocmark))];
		/*
		 * put it in the bucket in the vtag hash of assoc's for the
		 * system
		 */
		LIST_INSERT_HEAD(head, stcb, sctp_asocs);
		SCTP_INP_INFO_WUNLOCK();
		sctp_send_initiate(stcb->sctp_ep, stcb, SCTP_SO_NOT_LOCKED);
		return (1);
	}
	return (0);
}