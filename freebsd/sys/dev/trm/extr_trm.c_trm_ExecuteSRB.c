#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  status; scalar_t__ ccb_trmacb_ptr; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  void* u_long ;
struct TYPE_10__ {scalar_t__ ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_13__ {TYPE_3__* pFreeSRB; int /*<<< orphan*/  buffer_dmat; } ;
struct TYPE_12__ {void* length; int /*<<< orphan*/  address; } ;
struct TYPE_11__ {int SRBSGCount; struct TYPE_11__* pNextSRB; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  ScsiPhase; scalar_t__ SRBState; scalar_t__ SRBFlag; scalar_t__ SRBStatus; scalar_t__ MsgCnt; scalar_t__ TargetStatus; scalar_t__ AdaptStatus; scalar_t__ SRBSGIndex; void* SRBTotalXferLength; scalar_t__ RetryCnt; TYPE_4__* pSRBSGL; union ccb* pccb; } ;
typedef  TYPE_3__* PSRB ;
typedef  TYPE_4__* PSEG ;
typedef  TYPE_5__* PACB ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int /*<<< orphan*/  CAM_REQ_INPROG ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  PH_BUS_FREE ; 
 int /*<<< orphan*/  TRM_DPRINTF (char*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int splcam () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  trm_SendSRB (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
trm_ExecuteSRB(void *arg, bus_dma_segment_t *dm_segs, int nseg, int error)
{
	int		flags;
	PACB		pACB;
	PSRB		pSRB;
	union ccb	*ccb;
	u_long		totalxferlen=0;

	flags = splcam();
	pSRB = (PSRB)arg;
	ccb = pSRB->pccb;
	pACB = (PACB)ccb->ccb_h.ccb_trmacb_ptr;
	TRM_DPRINTF("trm_ExecuteSRB..........\n");        
	if (nseg != 0) {
		PSEG			psg;
		bus_dma_segment_t	*end_seg;
		int			op;

		/* Copy the segments into our SG list */
		end_seg = dm_segs + nseg;
		psg = pSRB->pSRBSGL;
		while (dm_segs < end_seg) {
			psg->address = dm_segs->ds_addr;
			psg->length = (u_long)dm_segs->ds_len;
			totalxferlen += dm_segs->ds_len;
			psg++;
			dm_segs++;
		}
		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
			op = BUS_DMASYNC_PREREAD;
		} else {
			op = BUS_DMASYNC_PREWRITE;
		}
		bus_dmamap_sync(pACB->buffer_dmat, pSRB->dmamap, op);
	}
	pSRB->RetryCnt = 0;
	pSRB->SRBTotalXferLength = totalxferlen;
	pSRB->SRBSGCount = nseg;
	pSRB->SRBSGIndex = 0;
	pSRB->AdaptStatus = 0;
	pSRB->TargetStatus = 0;
	pSRB->MsgCnt = 0;
	pSRB->SRBStatus = 0;
	pSRB->SRBFlag = 0;
	pSRB->SRBState = 0;
	pSRB->ScsiPhase = PH_BUS_FREE; /* SCSI bus free Phase */

	if (ccb->ccb_h.status != CAM_REQ_INPROG) {
		if (nseg != 0)
			bus_dmamap_unload(pACB->buffer_dmat, pSRB->dmamap);
		pSRB->pNextSRB = pACB->pFreeSRB;
		pACB->pFreeSRB = pSRB;
		xpt_done(ccb);
		splx(flags);
		return;
	}
	ccb->ccb_h.status |= CAM_SIM_QUEUED;
	trm_SendSRB(pACB, pSRB);
	splx(flags);
	return;
}