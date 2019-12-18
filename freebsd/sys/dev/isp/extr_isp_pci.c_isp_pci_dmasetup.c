#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct TYPE_10__ {int /*<<< orphan*/  status; } ;
struct ccb_scsiio {TYPE_2__ ccb_h; } ;
struct TYPE_11__ {int error; void* rq; struct ccb_scsiio* cmd_token; TYPE_4__* isp; } ;
typedef  TYPE_3__ mush_t ;
struct TYPE_9__ {int /*<<< orphan*/  dmat; } ;
struct TYPE_12__ {TYPE_1__ isp_osinfo; } ;
typedef  TYPE_4__ ispsoftc_t ;
struct TYPE_13__ {int /*<<< orphan*/  dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  CAM_REQ_TOO_BIG ; 
 int /*<<< orphan*/  CAM_UNREC_HBA_ERROR ; 
 int CMD_COMPLETE ; 
 int CMD_EAGAIN ; 
 int CMD_QUEUED ; 
 int EFBIG ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 int MUSHERR_NOQENTRIES ; 
 TYPE_8__* PISP_PCMD (struct ccb_scsiio*) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma2 ; 
 int /*<<< orphan*/  isp_prt (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
isp_pci_dmasetup(ispsoftc_t *isp, struct ccb_scsiio *csio, void *ff)
{
	mush_t mush, *mp;
	int error;

	mp = &mush;
	mp->isp = isp;
	mp->cmd_token = csio;
	mp->rq = ff;
	mp->error = 0;

	error = bus_dmamap_load_ccb(isp->isp_osinfo.dmat, PISP_PCMD(csio)->dmap,
	    (union ccb *)csio, dma2, mp, 0);
	if (error == EINPROGRESS) {
		bus_dmamap_unload(isp->isp_osinfo.dmat, PISP_PCMD(csio)->dmap);
		mp->error = EINVAL;
		isp_prt(isp, ISP_LOGERR, "deferred dma allocation not supported");
	} else if (error && mp->error == 0) {
#ifdef	DIAGNOSTIC
		isp_prt(isp, ISP_LOGERR, "error %d in dma mapping code", error);
#endif
		mp->error = error;
	}
	if (mp->error) {
		int retval = CMD_COMPLETE;
		if (mp->error == MUSHERR_NOQENTRIES) {
			retval = CMD_EAGAIN;
		} else if (mp->error == EFBIG) {
			csio->ccb_h.status = CAM_REQ_TOO_BIG;
		} else if (mp->error == EINVAL) {
			csio->ccb_h.status = CAM_REQ_INVALID;
		} else {
			csio->ccb_h.status = CAM_UNREC_HBA_ERROR;
		}
		return (retval);
	}
	return (CMD_QUEUED);
}