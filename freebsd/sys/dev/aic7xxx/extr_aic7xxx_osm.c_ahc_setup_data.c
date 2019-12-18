#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct scb {TYPE_4__* io_ctx; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  flags; struct hardware_scb* hscb; } ;
struct TYPE_5__ {int /*<<< orphan*/  cdb; } ;
struct hardware_scb {int cdb_len; TYPE_1__ shared_data; int /*<<< orphan*/  cdb32; } ;
struct TYPE_6__ {int /*<<< orphan*/  cdb_bytes; int /*<<< orphan*/  cdb_ptr; } ;
struct ccb_hdr {scalar_t__ func_code; int flags; } ;
struct ccb_scsiio {int cdb_len; TYPE_2__ cdb_io; scalar_t__ sense_resid; scalar_t__ resid; struct ccb_hdr ccb_h; } ;
struct cam_sim {int dummy; } ;
struct ahc_softc {int /*<<< orphan*/  buffer_dmat; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {TYPE_3__ ccb_h; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  SCB_CDB32_PTR ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  ahc_execute_scb ; 
 int /*<<< orphan*/  ahc_free_scb (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (struct cam_sim*,int) ; 

__attribute__((used)) static void
ahc_setup_data(struct ahc_softc *ahc, struct cam_sim *sim,
	       struct ccb_scsiio *csio, struct scb *scb)
{
	struct hardware_scb *hscb;
	struct ccb_hdr *ccb_h;
	int error;
	
	hscb = scb->hscb;
	ccb_h = &csio->ccb_h;
	
	csio->resid = 0;
	csio->sense_resid = 0;
	if (ccb_h->func_code == XPT_SCSI_IO) {
		hscb->cdb_len = csio->cdb_len;
		if ((ccb_h->flags & CAM_CDB_POINTER) != 0) {

			if (hscb->cdb_len > sizeof(hscb->cdb32)
			 || (ccb_h->flags & CAM_CDB_PHYS) != 0) {
				aic_set_transaction_status(scb,
							   CAM_REQ_INVALID);
				ahc_free_scb(ahc, scb);
				xpt_done((union ccb *)csio);
				return;
			}
			if (hscb->cdb_len > 12) {
				memcpy(hscb->cdb32, 
				       csio->cdb_io.cdb_ptr,
				       hscb->cdb_len);
				scb->flags |= SCB_CDB32_PTR;
			} else {
				memcpy(hscb->shared_data.cdb, 
				       csio->cdb_io.cdb_ptr,
				       hscb->cdb_len);
			}
		} else {
			if (hscb->cdb_len > 12) {
				memcpy(hscb->cdb32, csio->cdb_io.cdb_bytes,
				       hscb->cdb_len);
				scb->flags |= SCB_CDB32_PTR;
			} else {
				memcpy(hscb->shared_data.cdb,
				       csio->cdb_io.cdb_bytes,
				       hscb->cdb_len);
			}
		}
	}
		
	error = bus_dmamap_load_ccb(ahc->buffer_dmat,
				    scb->dmamap,
				    (union ccb *)csio,
				    ahc_execute_scb,
				    scb,
				    0);
	if (error == EINPROGRESS) {
		/*
		 * So as to maintain ordering,
		 * freeze the controller queue
		 * until our mapping is
		 * returned.
		 */
		xpt_freeze_simq(sim, /*count*/1);
		scb->io_ctx->ccb_h.status |= CAM_RELEASE_SIMQ;
	}
}