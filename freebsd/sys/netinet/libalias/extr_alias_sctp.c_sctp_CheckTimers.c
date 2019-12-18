#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_nat_assoc {scalar_t__ exp; scalar_t__ state; int /*<<< orphan*/  g_vtag; } ;
struct TYPE_2__ {scalar_t__ loc_time; size_t cur_loc; int /*<<< orphan*/ * TimerQ; } ;
struct libalias {scalar_t__ timeStamp; TYPE_1__ sctpNatTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct sctp_nat_assoc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RmSctpAssoc (struct libalias*,struct sctp_nat_assoc*) ; 
 scalar_t__ SN_CL ; 
 int /*<<< orphan*/  SN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG_DEBUG ; 
 int /*<<< orphan*/  SN_LOG_INFO ; 
 size_t SN_TIMER_QUEUE_SIZE ; 
 int /*<<< orphan*/  SN_TO_NODIR ; 
 int /*<<< orphan*/  freeGlobalAddressList (struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  logsctperror (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_AddTimeOut (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  sn_free (struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  timer_Q ; 

void
sctp_CheckTimers(struct libalias *la)
{
	struct sctp_nat_assoc *assoc;

	LIBALIAS_LOCK_ASSERT(la);
	while(la->timeStamp >= la->sctpNatTimer.loc_time) {
		while (!LIST_EMPTY(&la->sctpNatTimer.TimerQ[la->sctpNatTimer.cur_loc])) {
			assoc = LIST_FIRST(&la->sctpNatTimer.TimerQ[la->sctpNatTimer.cur_loc]);
			//SLIST_REMOVE_HEAD(&la->sctpNatTimer.TimerQ[la->sctpNatTimer.cur_loc], timer_Q);
			LIST_REMOVE(assoc, timer_Q);
			if (la->timeStamp >= assoc->exp) { /* state expired */
				SN_LOG(((assoc->state == SN_CL) ? (SN_LOG_DEBUG) : (SN_LOG_INFO)),
				    logsctperror("Timer Expired", assoc->g_vtag, assoc->state, SN_TO_NODIR));
				RmSctpAssoc(la, assoc);
				freeGlobalAddressList(assoc);
				sn_free(assoc);
			} else {/* state not expired, reschedule timer*/
				sctp_AddTimeOut(la, assoc);
			}
		}
		/* Goto next location in the timer queue*/
		++la->sctpNatTimer.loc_time;
		if (++la->sctpNatTimer.cur_loc >= SN_TIMER_QUEUE_SIZE)
			la->sctpNatTimer.cur_loc = 0;
	}
}