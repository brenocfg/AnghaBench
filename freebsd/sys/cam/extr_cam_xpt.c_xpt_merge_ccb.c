#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  func_code; int /*<<< orphan*/  retry_count; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct ccb_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 

void
xpt_merge_ccb(union ccb *master_ccb, union ccb *slave_ccb)
{

	/*
	 * Pull fields that are valid for peripheral drivers to set
	 * into the master CCB along with the CCB "payload".
	 */
	master_ccb->ccb_h.retry_count = slave_ccb->ccb_h.retry_count;
	master_ccb->ccb_h.func_code = slave_ccb->ccb_h.func_code;
	master_ccb->ccb_h.timeout = slave_ccb->ccb_h.timeout;
	master_ccb->ccb_h.flags = slave_ccb->ccb_h.flags;
	bcopy(&(&slave_ccb->ccb_h)[1], &(&master_ccb->ccb_h)[1],
	      sizeof(union ccb) - sizeof(struct ccb_hdr));
}