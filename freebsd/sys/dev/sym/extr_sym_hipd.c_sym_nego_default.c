#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* tcb_p ;
typedef  TYPE_4__* hcb_p ;
typedef  TYPE_5__* ccb_p ;
struct TYPE_19__ {int nego_status; } ;
struct TYPE_18__ {void** msgout; void** msgin; int /*<<< orphan*/  maxoffs; int /*<<< orphan*/  minsync; } ;
struct TYPE_15__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  period; int /*<<< orphan*/  options; } ;
struct TYPE_16__ {TYPE_1__ goal; } ;
struct TYPE_17__ {TYPE_2__ tinfo; } ;

/* Variables and functions */
 void* M_NOOP ; 
#define  NS_PPR 130 
#define  NS_SYNC 129 
#define  NS_WIDE 128 
 int /*<<< orphan*/  sym_setpprot (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_setsync (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_setwide (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_nego_default(hcb_p np, tcb_p tp, ccb_p cp)
{
	/*
	 *  any error in negotiation:
	 *  fall back to default mode.
	 */
	switch (cp->nego_status) {
	case NS_PPR:
#if 0
		sym_setpprot (np, cp, 0, 0, 0, 0, 0, 0);
#else
		tp->tinfo.goal.options = 0;
		if (tp->tinfo.goal.period < np->minsync)
			tp->tinfo.goal.period = np->minsync;
		if (tp->tinfo.goal.offset > np->maxoffs)
			tp->tinfo.goal.offset = np->maxoffs;
#endif
		break;
	case NS_SYNC:
		sym_setsync (np, cp, 0, 0, 0, 0);
		break;
	case NS_WIDE:
		sym_setwide (np, cp, 0);
		break;
	}
	np->msgin [0] = M_NOOP;
	np->msgout[0] = M_NOOP;
	cp->nego_status = 0;
}