#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct ccb_scsiio {int dummy; } ;
struct TYPE_9__ {int error; void* rq; struct ccb_scsiio* cmd_token; TYPE_3__* isp; } ;
typedef  TYPE_2__ mush_t ;
struct TYPE_8__ {int /*<<< orphan*/  dmat; } ;
struct TYPE_10__ {TYPE_1__ isp_osinfo; } ;
typedef  TYPE_3__ ispsoftc_t ;
struct TYPE_11__ {int /*<<< orphan*/  dmap; } ;

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
 TYPE_7__* PISP_PCMD (struct ccb_scsiio*) ; 
 int /*<<< orphan*/  XS_SETERR (struct ccb_scsiio*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma2 ; 
 int /*<<< orphan*/  isp_prt (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
isp_sbus_dmasetup(ispsoftc_t *isp, struct ccb_scsiio *csio, void *ff)
{
	mush_t mush, *mp;
	int error;

	mp = &mush;
	mp->isp = isp;
	mp->cmd_token = csio;
	mp->rq = ff;
	mp->error = 0;

	error = bus_dmamap_load_ccb(isp->isp_osinfo.dmat,
	    PISP_PCMD(csio)->dmap, (union ccb *)csio, dma2, mp, 0);
	if (error == EINPROGRESS) {
		bus_dmamap_unload(isp->isp_osinfo.dmat, PISP_PCMD(csio)->dmap);
		mp->error = EINVAL;
		isp_prt(isp, ISP_LOGERR,
		    "deferred dma allocation not supported");
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
			XS_SETERR(csio, CAM_REQ_TOO_BIG);
		} else if (mp->error == EINVAL) {
			XS_SETERR(csio, CAM_REQ_INVALID);
		} else {
			XS_SETERR(csio, CAM_UNREC_HBA_ERROR);
		}
		return (retval);
	}
	return (CMD_QUEUED);
}