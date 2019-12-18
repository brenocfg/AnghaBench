#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int timeout; int /*<<< orphan*/  sim_links; TYPE_2__* sym_hcb_ptr; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  TYPE_2__* hcb_p ;
typedef  TYPE_3__* ccb_p ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  ch; scalar_t__ arg; union ccb* cam_ccb; } ;
struct TYPE_6__ {int /*<<< orphan*/  cam_ccbq; } ;

/* Variables and functions */
 int CAM_REQ_INPROG ; 
 int CAM_SIM_QUEUED ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_callout ; 
 int /*<<< orphan*/  sym_insque_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_qptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sym_enqueue_cam_ccb(ccb_p cp)
{
	hcb_p np;
	union ccb *ccb;

	ccb = cp->cam_ccb;
	np = (hcb_p) cp->arg;

	assert(!(ccb->ccb_h.status & CAM_SIM_QUEUED));
	ccb->ccb_h.status = CAM_REQ_INPROG;

	callout_reset_sbt(&cp->ch, SBT_1MS * ccb->ccb_h.timeout, 0, sym_callout,
	    (caddr_t)ccb, 0);
	ccb->ccb_h.status |= CAM_SIM_QUEUED;
	ccb->ccb_h.sym_hcb_ptr = np;

	sym_insque_tail(sym_qptr(&ccb->ccb_h.sim_links), &np->cam_ccbq);
}