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
struct mrsas_softc {int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  sim_1; int /*<<< orphan*/  sim_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 union ccb* xpt_alloc_ccb () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_periph ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

int
mrsas_bus_scan(struct mrsas_softc *sc)
{
	union ccb *ccb_0;
	union ccb *ccb_1;

	if ((ccb_0 = xpt_alloc_ccb()) == NULL) {
		return (ENOMEM);
	}
	if ((ccb_1 = xpt_alloc_ccb()) == NULL) {
		xpt_free_ccb(ccb_0);
		return (ENOMEM);
	}
	mtx_lock(&sc->sim_lock);
	if (xpt_create_path(&ccb_0->ccb_h.path, xpt_periph, cam_sim_path(sc->sim_0),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_free_ccb(ccb_0);
		xpt_free_ccb(ccb_1);
		mtx_unlock(&sc->sim_lock);
		return (EIO);
	}
	if (xpt_create_path(&ccb_1->ccb_h.path, xpt_periph, cam_sim_path(sc->sim_1),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_free_ccb(ccb_0);
		xpt_free_ccb(ccb_1);
		mtx_unlock(&sc->sim_lock);
		return (EIO);
	}
	mtx_unlock(&sc->sim_lock);
	xpt_rescan(ccb_0);
	xpt_rescan(ccb_1);

	return (0);
}