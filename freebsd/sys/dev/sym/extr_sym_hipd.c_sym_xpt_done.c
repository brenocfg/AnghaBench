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
struct TYPE_4__ {int status; int /*<<< orphan*/ * sym_hcb_ptr; int /*<<< orphan*/  sim_links; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  hcb_p ;
typedef  TYPE_2__* ccb_p ;
struct TYPE_5__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_qptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_remque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void sym_xpt_done(hcb_p np, union ccb *ccb, ccb_p cp)
{

	SYM_LOCK_ASSERT(MA_OWNED);

	if (ccb->ccb_h.status & CAM_SIM_QUEUED) {
		callout_stop(&cp->ch);
		sym_remque(sym_qptr(&ccb->ccb_h.sim_links));
		ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
		ccb->ccb_h.sym_hcb_ptr = NULL;
	}
	xpt_done(ccb);
}