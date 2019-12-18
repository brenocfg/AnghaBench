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
struct TYPE_2__ {int flags; int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct CommandControlBlock {int srb_flags; scalar_t__ srb_state; int /*<<< orphan*/  dm_segs_dmamap; int /*<<< orphan*/  ccb_callout; union ccb* pccb; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {int srboutstandingcount; int acb_flags; int maxOutstanding; int /*<<< orphan*/  pktReturnCount; int /*<<< orphan*/  dm_segs_dmat; } ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
 int ACB_F_CAM_DEV_QFRZN ; 
 scalar_t__ ARCMSR_SRB_TIMEOUT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int SRB_FLAG_TIMER_START ; 
 int /*<<< orphan*/  arcmsr_free_srb (struct CommandControlBlock*) ; 
 int /*<<< orphan*/  atomic_subtract_int (int*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void arcmsr_srb_complete(struct CommandControlBlock *srb, int stand_flag)
{
	struct AdapterControlBlock *acb = srb->acb;
	union ccb *pccb = srb->pccb;

	if(srb->srb_flags & SRB_FLAG_TIMER_START)
		callout_stop(&srb->ccb_callout);
	if((pccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		bus_dmasync_op_t op;

		if((pccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
			op = BUS_DMASYNC_POSTREAD;
		} else {
			op = BUS_DMASYNC_POSTWRITE;
		}
		bus_dmamap_sync(acb->dm_segs_dmat, srb->dm_segs_dmamap, op);
		bus_dmamap_unload(acb->dm_segs_dmat, srb->dm_segs_dmamap);
	}
	if(stand_flag == 1) {
		atomic_subtract_int(&acb->srboutstandingcount, 1);
		if((acb->acb_flags & ACB_F_CAM_DEV_QFRZN) && (
		acb->srboutstandingcount < (acb->maxOutstanding -10))) {
			acb->acb_flags &= ~ACB_F_CAM_DEV_QFRZN;
			pccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		}
	}
	if(srb->srb_state != ARCMSR_SRB_TIMEOUT)
		arcmsr_free_srb(srb);
	acb->pktReturnCount++;
	xpt_done(pccb);
}