#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  TYPE_4__* tcb_p ;
typedef  TYPE_5__* hcb_p ;
typedef  TYPE_6__* ccb_p ;
struct TYPE_15__ {size_t target; int nego_status; } ;
struct TYPE_14__ {int features; TYPE_4__* target; } ;
struct TYPE_11__ {int options; scalar_t__ width; scalar_t__ period; scalar_t__ offset; } ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ period; scalar_t__ offset; } ;
struct TYPE_12__ {TYPE_2__ goal; TYPE_1__ current; } ;
struct TYPE_13__ {TYPE_6__* nego_cp; TYPE_3__ tinfo; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_NEGO ; 
 int FE_U3EN ; 
 int M_EXTENDED ; 
 int M_X_PPR_REQ ; 
 int M_X_SYNC_REQ ; 
 int M_X_WIDE_REQ ; 
#define  NS_PPR 130 
#define  NS_SYNC 129 
#define  NS_WIDE 128 
 int PPR_OPT_DT ; 
 int PPR_OPT_MASK ; 
 int /*<<< orphan*/  sym_print_msg (TYPE_6__*,char*,int*) ; 

__attribute__((used)) static int sym_prepare_nego(hcb_p np, ccb_p cp, int nego, u_char *msgptr)
{
	tcb_p tp = &np->target[cp->target];
	int msglen = 0;

	/*
	 *  Early C1010 chips need a work-around for DT
	 *  data transfer to work.
	 */
	if (!(np->features & FE_U3EN))
		tp->tinfo.goal.options = 0;
	/*
	 *  negotiate using PPR ?
	 */
	if (tp->tinfo.goal.options & PPR_OPT_MASK)
		nego = NS_PPR;
	/*
	 *  negotiate wide transfers ?
	 */
	else if (tp->tinfo.current.width != tp->tinfo.goal.width)
		nego = NS_WIDE;
	/*
	 *  negotiate synchronous transfers?
	 */
	else if (tp->tinfo.current.period != tp->tinfo.goal.period ||
		 tp->tinfo.current.offset != tp->tinfo.goal.offset)
		nego = NS_SYNC;

	switch (nego) {
	case NS_SYNC:
		msgptr[msglen++] = M_EXTENDED;
		msgptr[msglen++] = 3;
		msgptr[msglen++] = M_X_SYNC_REQ;
		msgptr[msglen++] = tp->tinfo.goal.period;
		msgptr[msglen++] = tp->tinfo.goal.offset;
		break;
	case NS_WIDE:
		msgptr[msglen++] = M_EXTENDED;
		msgptr[msglen++] = 2;
		msgptr[msglen++] = M_X_WIDE_REQ;
		msgptr[msglen++] = tp->tinfo.goal.width;
		break;
	case NS_PPR:
		msgptr[msglen++] = M_EXTENDED;
		msgptr[msglen++] = 6;
		msgptr[msglen++] = M_X_PPR_REQ;
		msgptr[msglen++] = tp->tinfo.goal.period;
		msgptr[msglen++] = 0;
		msgptr[msglen++] = tp->tinfo.goal.offset;
		msgptr[msglen++] = tp->tinfo.goal.width;
		msgptr[msglen++] = tp->tinfo.goal.options & PPR_OPT_DT;
		break;
	}

	cp->nego_status = nego;

	if (nego) {
		tp->nego_cp = cp; /* Keep track a nego will be performed */
		if (DEBUG_FLAGS & DEBUG_NEGO) {
			sym_print_msg(cp, nego == NS_SYNC ? "sync msgout" :
					  nego == NS_WIDE ? "wide msgout" :
					  "ppr msgout", msgptr);
		}
	}

	return msglen;
}