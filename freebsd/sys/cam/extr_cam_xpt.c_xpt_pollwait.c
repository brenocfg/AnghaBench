#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; TYPE_2__* path; } ;
union ccb {TYPE_3__ ccb_h; } ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  sim; } ;

/* Variables and functions */
 int CAM_CMD_TIMEOUT ; 
 int CAM_REQ_INPROG ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  xpt_sim_poll (int /*<<< orphan*/ ) ; 

void
xpt_pollwait(union ccb *start_ccb, uint32_t timeout)
{

	while (--timeout > 0) {
		xpt_sim_poll(start_ccb->ccb_h.path->bus->sim);
		if ((start_ccb->ccb_h.status & CAM_STATUS_MASK)
		    != CAM_REQ_INPROG)
			break;
		DELAY(100);
	}

	if (timeout == 0) {
		/*
		 * XXX Is it worth adding a sim_timeout entry
		 * point so we can attempt recovery?  If
		 * this is only used for dumps, I don't think
		 * it is.
		 */
		start_ccb->ccb_h.status = CAM_CMD_TIMEOUT;
	}
}