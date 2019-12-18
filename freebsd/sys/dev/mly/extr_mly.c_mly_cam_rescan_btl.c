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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct mly_softc {int /*<<< orphan*/ * mly_cam_sim; } ;

/* Variables and functions */
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int,char*,int,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  mly_printf (struct mly_softc*,char*) ; 
 union ccb* xpt_alloc_ccb () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
mly_cam_rescan_btl(struct mly_softc *sc, int bus, int target)
{
    union ccb	*ccb;

    debug_called(1);

    if ((ccb = xpt_alloc_ccb()) == NULL) {
	mly_printf(sc, "rescan failed (can't allocate CCB)\n");
	return;
    }
    if (xpt_create_path(&ccb->ccb_h.path, NULL,
	    cam_sim_path(sc->mly_cam_sim[bus]), target, 0) != CAM_REQ_CMP) {
	mly_printf(sc, "rescan failed (can't create path)\n");
	xpt_free_ccb(ccb);
	return;
    }
    debug(1, "rescan target %d:%d", bus, target);
    xpt_rescan(ccb);
}