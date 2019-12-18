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
struct TYPE_2__ {int /*<<< orphan*/  (* cbfcnp ) (struct cam_periph*,union ccb*) ;int /*<<< orphan*/  (* ppriv_ptr1 ) (struct cam_periph*,union ccb*) ;int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cam_periph*,union ccb*) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_boot () ; 

__attribute__((used)) static void
xpt_rescan_done(struct cam_periph *periph, union ccb *done_ccb)
{

	if (done_ccb->ccb_h.ppriv_ptr1 == NULL) {
		xpt_free_path(done_ccb->ccb_h.path);
		xpt_free_ccb(done_ccb);
	} else {
		done_ccb->ccb_h.cbfcnp = done_ccb->ccb_h.ppriv_ptr1;
		(*done_ccb->ccb_h.cbfcnp)(periph, done_ccb);
	}
	xpt_release_boot();
}