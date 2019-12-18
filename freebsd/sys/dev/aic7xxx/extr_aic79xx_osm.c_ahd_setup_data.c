#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct scb {TYPE_6__* io_ctx; int /*<<< orphan*/  dmamap; struct hardware_scb* hscb; } ;
struct TYPE_7__ {int /*<<< orphan*/  cdblen; int /*<<< orphan*/  cdbptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  cdb; TYPE_1__ cdb_from_host; } ;
struct TYPE_9__ {TYPE_2__ idata; } ;
struct hardware_scb {int /*<<< orphan*/  cdb_len; TYPE_3__ shared_data; } ;
struct TYPE_10__ {scalar_t__ cdb_bytes; scalar_t__ cdb_ptr; } ;
struct ccb_hdr {scalar_t__ func_code; int flags; } ;
struct ccb_scsiio {TYPE_4__ cdb_io; int /*<<< orphan*/  cdb_len; scalar_t__ sense_resid; scalar_t__ resid; struct ccb_hdr ccb_h; } ;
struct cam_sim {int dummy; } ;
struct ahd_softc {int /*<<< orphan*/  buffer_dmat; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_12__ {TYPE_5__ ccb_h; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  MAX_CDB_LEN ; 
 int /*<<< orphan*/  SCB_CDB_LEN_PTR ; 
 scalar_t__ XPT_SCSI_IO ; 
 int /*<<< orphan*/  ahd_execute_scb ; 
 int /*<<< orphan*/  ahd_free_scb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  aic_htole64 (uintptr_t) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (struct cam_sim*,int) ; 

__attribute__((used)) static void
ahd_setup_data(struct ahd_softc *ahd, struct cam_sim *sim,
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

			if (hscb->cdb_len > MAX_CDB_LEN
			 && (ccb_h->flags & CAM_CDB_PHYS) == 0) {

				/*
				 * Should CAM start to support CDB sizes
				 * greater than 16 bytes, we could use
				 * the sense buffer to store the CDB.
				 */
				aic_set_transaction_status(scb,
							   CAM_REQ_INVALID);
				ahd_free_scb(ahd, scb);
				xpt_done((union ccb *)csio);
				return;
			}
			if ((ccb_h->flags & CAM_CDB_PHYS) != 0) {
				hscb->shared_data.idata.cdb_from_host.cdbptr =
				   aic_htole64((uintptr_t)csio->cdb_io.cdb_ptr);
				hscb->shared_data.idata.cdb_from_host.cdblen =
				   csio->cdb_len;
				hscb->cdb_len |= SCB_CDB_LEN_PTR;
			} else {
				memcpy(hscb->shared_data.idata.cdb, 
				       csio->cdb_io.cdb_ptr,
				       hscb->cdb_len);
			}
		} else {
			if (hscb->cdb_len > MAX_CDB_LEN) {

				aic_set_transaction_status(scb,
							   CAM_REQ_INVALID);
				ahd_free_scb(ahd, scb);
				xpt_done((union ccb *)csio);
				return;
			}
			memcpy(hscb->shared_data.idata.cdb,
			       csio->cdb_io.cdb_bytes, hscb->cdb_len);
		}
	}
		
	error = bus_dmamap_load_ccb(ahd->buffer_dmat,
				    scb->dmamap,
				    (union ccb *)csio,
				    ahd_execute_scb,
				    scb, /*flags*/0);
	if (error == EINPROGRESS) {
		/*
		 * So as to maintain ordering, freeze the controller queue
		 * until our mapping is returned.
		 */
		xpt_freeze_simq(sim, /*count*/1);
		scb->io_ctx->ccb_h.status |= CAM_RELEASE_SIMQ;
	}
}