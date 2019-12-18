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
struct TYPE_2__ {int /*<<< orphan*/  cbfcnp; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cam_periph_done_panic ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_path_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cam_periph_done(struct cam_periph *periph, union ccb *done_ccb)
{

	/* Caller will release the CCB */
	xpt_path_assert(done_ccb->ccb_h.path, MA_OWNED);
	done_ccb->ccb_h.cbfcnp = cam_periph_done_panic;
	wakeup(&done_ccb->ccb_h.cbfcnp);
}