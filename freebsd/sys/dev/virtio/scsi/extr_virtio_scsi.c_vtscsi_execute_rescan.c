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
typedef  int /*<<< orphan*/  target_id_t ;
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_sim; } ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  scalar_t__ cam_status ;

/* Variables and functions */
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  VTSCSI_ERROR ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
vtscsi_execute_rescan(struct vtscsi_softc *sc, target_id_t target_id,
    lun_id_t lun_id)
{
	union ccb *ccb;
	cam_status status;

	ccb = xpt_alloc_ccb_nowait();
	if (ccb == NULL) {
		vtscsi_dprintf(sc, VTSCSI_ERROR, "cannot allocate CCB\n");
		return;
	}

	status = xpt_create_path(&ccb->ccb_h.path, NULL,
	    cam_sim_path(sc->vtscsi_sim), target_id, lun_id);
	if (status != CAM_REQ_CMP) {
		xpt_free_ccb(ccb);
		return;
	}

	xpt_rescan(ccb);
}