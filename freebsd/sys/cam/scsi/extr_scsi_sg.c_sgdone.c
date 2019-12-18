#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct sg_rdwr* ccb_rdwr; } ;
struct TYPE_3__ {int ccb_type; int flags; } ;
struct ccb_scsiio {int tag_action; TYPE_1__ ccb_h; int /*<<< orphan*/  dxfer_len; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_scsiio csio; } ;
struct sg_softc {int /*<<< orphan*/  device_stats; } ;
struct sg_rdwr {int state; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int CAM_DIR_OUT ; 
 int /*<<< orphan*/  DEVSTAT_NO_DATA ; 
 int /*<<< orphan*/  DEVSTAT_READ ; 
 int /*<<< orphan*/  DEVSTAT_WRITE ; 
#define  SG_CCB_RDWR_IO 128 
 int SG_RDWR_DONE ; 
 int /*<<< orphan*/  devstat_end_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (struct sg_rdwr*) ; 

__attribute__((used)) static void
sgdone(struct cam_periph *periph, union ccb *done_ccb)
{
	struct sg_softc *softc;
	struct ccb_scsiio *csio;

	softc = (struct sg_softc *)periph->softc;
	csio = &done_ccb->csio;
	switch (csio->ccb_h.ccb_type) {
	case SG_CCB_RDWR_IO:
	{
		struct sg_rdwr *rdwr;
		int state;

		devstat_end_transaction(softc->device_stats,
					csio->dxfer_len,
					csio->tag_action & 0xf,
					((csio->ccb_h.flags & CAM_DIR_MASK) ==
					CAM_DIR_NONE) ? DEVSTAT_NO_DATA :
					(csio->ccb_h.flags & CAM_DIR_OUT) ?
					DEVSTAT_WRITE : DEVSTAT_READ,
					NULL, NULL);

		rdwr = done_ccb->ccb_h.ccb_rdwr;
		state = rdwr->state;
		rdwr->state = SG_RDWR_DONE;
		wakeup(rdwr);
		break;
	}
	default:
		panic("unknown sg CCB type");
	}
}