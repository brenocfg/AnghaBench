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
struct TYPE_6__ {scalar_t__ io_type; int status; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ ext_data_filled; } ;
union ctl_io {TYPE_2__ io_hdr; TYPE_1__ scsiio; } ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_4__ ccb_h; } ;
struct ctlfe_lun_softc {int /*<<< orphan*/  work_queue; } ;
struct cam_periph {scalar_t__ softc; } ;
struct TYPE_7__ {int /*<<< orphan*/  stqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CTL_FLAG_DMA_QUEUED ; 
 int /*<<< orphan*/  CTL_FLAG_STATUS_QUEUED ; 
 scalar_t__ CTL_IO_SCSI ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 union ccb* PRIV_CCB (union ctl_io*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 TYPE_3__ periph_links ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctlfe_datamove(union ctl_io *io)
{
	union ccb *ccb;
	struct cam_periph *periph;
	struct ctlfe_lun_softc *softc;

	KASSERT(io->io_hdr.io_type == CTL_IO_SCSI,
	    ("Unexpected io_type (%d) in ctlfe_datamove", io->io_hdr.io_type));

	io->scsiio.ext_data_filled = 0;
	ccb = PRIV_CCB(io);
	periph = xpt_path_periph(ccb->ccb_h.path);
	cam_periph_lock(periph);
	softc = (struct ctlfe_lun_softc *)periph->softc;
	io->io_hdr.flags |= CTL_FLAG_DMA_QUEUED;
	if ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE)
		io->io_hdr.flags |= CTL_FLAG_STATUS_QUEUED;
	STAILQ_INSERT_TAIL(&softc->work_queue, &ccb->ccb_h,
			  periph_links.stqe);
	xpt_schedule(periph, CAM_PRIORITY_NORMAL);
	cam_periph_unlock(periph);
}