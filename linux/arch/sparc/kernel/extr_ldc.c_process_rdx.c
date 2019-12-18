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
struct TYPE_3__ {int /*<<< orphan*/  ackid; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct ldc_packet {scalar_t__ stype; int /*<<< orphan*/  seqid; TYPE_2__ u; int /*<<< orphan*/  env; } ;
struct ldc_channel {int /*<<< orphan*/  hs_state; int /*<<< orphan*/  rcv_nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int LDC_ABORT (struct ldc_channel*) ; 
 int LDC_EVENT_UP ; 
 int /*<<< orphan*/  LDC_HS_COMPLETE ; 
 scalar_t__ LDC_INFO ; 
 int /*<<< orphan*/  LDC_STATE_CONNECTED ; 
 int /*<<< orphan*/  ldc_set_state (struct ldc_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_seq_ok (struct ldc_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_rdx(struct ldc_channel *lp,
		       struct ldc_packet *p)
{
	ldcdbg(HS, "GOT RDX stype[%x] seqid[%x] env[%x] ackid[%x]\n",
	       p->stype, p->seqid, p->env, p->u.r.ackid);

	if (p->stype != LDC_INFO ||
	    !(rx_seq_ok(lp, p->seqid)))
		return LDC_ABORT(lp);

	lp->rcv_nxt = p->seqid;

	lp->hs_state = LDC_HS_COMPLETE;
	ldc_set_state(lp, LDC_STATE_CONNECTED);

	return LDC_EVENT_UP;
}