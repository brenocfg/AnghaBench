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
struct ldc_packet {scalar_t__ stype; scalar_t__ env; int /*<<< orphan*/  seqid; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct ldc_channel {scalar_t__ hs_state; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  snd_nxt; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int LDC_ABORT (struct ldc_channel*) ; 
 scalar_t__ LDC_HS_GOTVERS ; 
 scalar_t__ LDC_HS_SENTRTR ; 
 scalar_t__ LDC_INFO ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ send_rtr (struct ldc_channel*) ; 

__attribute__((used)) static int process_rts(struct ldc_channel *lp,
		       struct ldc_packet *p)
{
	ldcdbg(HS, "GOT RTS stype[%x] seqid[%x] env[%x]\n",
	       p->stype, p->seqid, p->env);

	if (p->stype     != LDC_INFO	   ||
	    lp->hs_state != LDC_HS_GOTVERS ||
	    p->env       != lp->cfg.mode)
		return LDC_ABORT(lp);

	lp->snd_nxt = p->seqid;
	lp->rcv_nxt = p->seqid;
	lp->hs_state = LDC_HS_SENTRTR;
	if (send_rtr(lp))
		return LDC_ABORT(lp);

	return 0;
}