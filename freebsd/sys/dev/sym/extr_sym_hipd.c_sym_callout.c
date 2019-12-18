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
struct TYPE_2__ {int func_code; int /*<<< orphan*/  sym_hcb_ptr; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_LOCK () ; 
 int /*<<< orphan*/  SYM_UNLOCK () ; 
#define  XPT_SCSI_IO 128 
 int /*<<< orphan*/  sym_abort_scsiio (int /*<<< orphan*/ ,union ccb*,int) ; 

__attribute__((used)) static void sym_callout(void *arg)
{
	union ccb *ccb = (union ccb *) arg;
	hcb_p np = ccb->ccb_h.sym_hcb_ptr;

	/*
	 *  Check that the CAM CCB is still queued.
	 */
	if (!np)
		return;

	SYM_LOCK();

	switch(ccb->ccb_h.func_code) {
	case XPT_SCSI_IO:
		(void) sym_abort_scsiio(np, ccb, 1);
		break;
	default:
		break;
	}

	SYM_UNLOCK();
}