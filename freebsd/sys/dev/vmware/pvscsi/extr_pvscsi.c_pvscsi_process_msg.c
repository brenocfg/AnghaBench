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
struct pvscsi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  sim; } ;
struct pvscsi_ring_msg_dev_status_changed {int const type; int /*<<< orphan*/ * lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct pvscsi_ring_msg_desc {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
#define  PVSCSI_MSG_DEV_ADDED 129 
#define  PVSCSI_MSG_DEV_REMOVED 128 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
pvscsi_process_msg(struct pvscsi_softc *sc, struct pvscsi_ring_msg_desc *e)
{
	struct pvscsi_ring_msg_dev_status_changed *desc;

	union ccb *ccb;
	switch (e->type) {
	case PVSCSI_MSG_DEV_ADDED:
	case PVSCSI_MSG_DEV_REMOVED: {
		desc = (struct pvscsi_ring_msg_dev_status_changed *)e;

		device_printf(sc->dev, "MSG: device %s at scsi%u:%u:%u\n",
		    desc->type == PVSCSI_MSG_DEV_ADDED ? "addition" : "removal",
		    desc->bus, desc->target, desc->lun[1]);

		ccb = xpt_alloc_ccb_nowait();
		if (ccb == NULL) {
			device_printf(sc->dev,
			    "Error allocating CCB for dev change.\n");
			break;
		}

		if (xpt_create_path(&ccb->ccb_h.path, NULL,
		    cam_sim_path(sc->sim), desc->target, desc->lun[1])
		    != CAM_REQ_CMP) {
			device_printf(sc->dev,
			    "Error creating path for dev change.\n");
			xpt_free_ccb(ccb);
			break;
		}

		xpt_rescan(ccb);
	} break;
	default:
		device_printf(sc->dev, "Unknown msg type 0x%x\n", e->type);
	};
}