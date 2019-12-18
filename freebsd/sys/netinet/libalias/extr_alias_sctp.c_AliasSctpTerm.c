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
struct sctp_nat_assoc {int dummy; } ;
struct TYPE_2__ {struct sctp_nat_assoc* TimerQ; } ;
struct libalias {TYPE_1__ sctpNatTimer; struct sctp_nat_assoc* sctpTableGlobal; struct sctp_nat_assoc* sctpTableLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 struct sctp_nat_assoc* LIST_FIRST (struct sctp_nat_assoc*) ; 
 struct sctp_nat_assoc* LIST_NEXT (struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SN_LOG_EVENT ; 
 int SN_TIMER_QUEUE_SIZE ; 
 int /*<<< orphan*/  SctpAliasLog (char*) ; 
 int /*<<< orphan*/  freeGlobalAddressList (struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  sn_free (struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  timer_Q ; 

void AliasSctpTerm(struct libalias *la)
{
	struct sctp_nat_assoc *assoc1, *assoc2;
	int                   i;

	LIBALIAS_LOCK_ASSERT(la);
	SN_LOG(SN_LOG_EVENT,
	    SctpAliasLog("Removing SCTP NAT Instance\n"));
	for (i = 0; i < SN_TIMER_QUEUE_SIZE; i++) {
		assoc1 = LIST_FIRST(&la->sctpNatTimer.TimerQ[i]);
		while (assoc1 != NULL) {
			freeGlobalAddressList(assoc1);
			assoc2 = LIST_NEXT(assoc1, timer_Q);
			sn_free(assoc1);
			assoc1 = assoc2;
		}
	}

	sn_free(la->sctpTableLocal);
	sn_free(la->sctpTableGlobal);
	sn_free(la->sctpNatTimer.TimerQ);
}