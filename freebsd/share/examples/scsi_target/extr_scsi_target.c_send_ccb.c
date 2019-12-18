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
struct TYPE_4__ {int priority; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; TYPE_1__ pinfo; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_3__ ccb_h; } ;
typedef  int /*<<< orphan*/  ccb ;
struct TYPE_5__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PROVIDE_FAIL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XPT_FC_IS_QUEUED (union ccb*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  pending_queue ; 
 TYPE_2__ periph_links ; 
 int /*<<< orphan*/  targ_fd ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,union ccb**,int) ; 

void
send_ccb(union ccb *ccb, int priority)
{
	if (debug)
		warnx("sending ccb (%#x)", ccb->ccb_h.func_code);
	ccb->ccb_h.pinfo.priority = priority;
	if (XPT_FC_IS_QUEUED(ccb)) {
		TAILQ_INSERT_TAIL(&pending_queue, &ccb->ccb_h,
				  periph_links.tqe);
	}
	if (write(targ_fd, &ccb, sizeof(ccb)) != sizeof(ccb)) {
		warn("write ccb");
		ccb->ccb_h.status = CAM_PROVIDE_FAIL;
	}
}