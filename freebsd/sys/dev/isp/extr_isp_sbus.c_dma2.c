#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ func_code; } ;
struct ccb_scsiio {TYPE_1__ ccb_h; } ;
struct TYPE_9__ {int error; int /*<<< orphan*/  rq; struct ccb_scsiio* cmd_token; TYPE_4__* isp; } ;
typedef  TYPE_3__ mush_t ;
struct TYPE_8__ {int /*<<< orphan*/  dmat; } ;
struct TYPE_10__ {TYPE_2__ isp_osinfo; } ;
typedef  TYPE_4__ ispsoftc_t ;
typedef  int /*<<< orphan*/  isp_ddir_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
struct TYPE_11__ {int /*<<< orphan*/  dmap; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 scalar_t__ CMD_QUEUED ; 
 int /*<<< orphan*/  ISP_FROM_DEVICE ; 
 int /*<<< orphan*/  ISP_NOXFR ; 
 int /*<<< orphan*/  ISP_TO_DEVICE ; 
 int MUSHERR_NOQENTRIES ; 
 TYPE_6__* PISP_PCMD (struct ccb_scsiio*) ; 
 scalar_t__ XPT_CONT_TARGET_IO ; 
 int /*<<< orphan*/  XS_XFRLEN (struct ccb_scsiio*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isp_send_cmd (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dma2(void *arg, bus_dma_segment_t *dm_segs, int nseg, int error)
{
	mush_t *mp = (mush_t *) arg;
	ispsoftc_t *isp = mp->isp;
	struct ccb_scsiio *csio = mp->cmd_token;
	isp_ddir_t ddir;
	int sdir;

	if (error) {
		mp->error = error;
		return;
	}
	if (nseg == 0) {
		ddir = ISP_NOXFR;
	} else {
		if ((csio->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
			ddir = ISP_FROM_DEVICE;
		} else {
			ddir = ISP_TO_DEVICE;
		}
		if ((csio->ccb_h.func_code == XPT_CONT_TARGET_IO) ^
		    ((csio->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN)) {
			sdir = BUS_DMASYNC_PREREAD;
		} else {
			sdir = BUS_DMASYNC_PREWRITE;
		}
		bus_dmamap_sync(isp->isp_osinfo.dmat, PISP_PCMD(csio)->dmap,
		    sdir);
	}

	if (isp_send_cmd(isp, mp->rq, dm_segs, nseg, XS_XFRLEN(csio),
	    ddir, NULL) != CMD_QUEUED) {
		mp->error = MUSHERR_NOQENTRIES;
	}
}