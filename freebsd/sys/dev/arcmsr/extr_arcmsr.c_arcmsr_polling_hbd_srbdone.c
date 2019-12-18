#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct HBD_MessageUnit0 {int doneq_index; TYPE_1__* done_qbuffer; } ;
struct CommandControlBlock {scalar_t__ srb_state; TYPE_3__* pccb; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {scalar_t__ srboutstandingcount; int pci_unit; scalar_t__ vir2phy_offset; int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; scalar_t__ pmu; } ;
struct TYPE_5__ {int target_id; int /*<<< orphan*/  status; scalar_t__ target_lun; } ;
struct TYPE_6__ {TYPE_2__ ccb_h; } ;
struct TYPE_4__ {int addressLow; } ;

/* Variables and functions */
 int ARCMSR_SRBREPLY_FLAG_ERROR_MODE1 ; 
 scalar_t__ ARCMSR_SRB_ABORTED ; 
 scalar_t__ ARCMSR_SRB_START ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int TRUE ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int arcmsr_get_doneq_index (struct HBD_MessageUnit0*) ; 
 int /*<<< orphan*/  arcmsr_report_srb_state (struct AdapterControlBlock*,struct CommandControlBlock*,int) ; 
 int /*<<< orphan*/  arcmsr_srb_complete (struct CommandControlBlock*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outboundlist_read_pointer ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void arcmsr_polling_hbd_srbdone(struct AdapterControlBlock *acb, struct CommandControlBlock *poll_srb)
{
	struct HBD_MessageUnit0 *phbdmu = (struct HBD_MessageUnit0 *)acb->pmu;
	struct CommandControlBlock *srb;
	u_int32_t flag_srb, poll_srb_done=0, poll_count=0;
	u_int32_t outbound_write_pointer;
	u_int16_t	error, doneq_index;

polling_ccb_retry:
	poll_count++;
	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	while(1) {
		outbound_write_pointer = phbdmu->done_qbuffer[0].addressLow;
		doneq_index = phbdmu->doneq_index;
		if ((outbound_write_pointer & 0xFF) == (doneq_index & 0xFF)) {
			if(poll_srb_done) {
				break;/*chip FIFO no ccb for completion already*/
			} else {
				UDELAY(25000);
				if ((poll_count > 100) && (poll_srb != NULL)) {
					break;
				}
				if (acb->srboutstandingcount == 0) {
					break;
				}
				goto polling_ccb_retry;
			}
		}
		doneq_index = arcmsr_get_doneq_index(phbdmu);
		flag_srb = phbdmu->done_qbuffer[(doneq_index & 0xFF)+1].addressLow;
		/* check if command done with no error*/
		srb = (struct CommandControlBlock *)(acb->vir2phy_offset+(flag_srb & 0xFFFFFFE0));/*frame must be 32 bytes aligned*/
		error = (flag_srb & ARCMSR_SRBREPLY_FLAG_ERROR_MODE1) ? TRUE : FALSE;
		CHIP_REG_WRITE32(HBD_MessageUnit, 0, outboundlist_read_pointer, doneq_index);
		if (poll_srb != NULL)
			poll_srb_done = (srb == poll_srb) ? 1:0;
		if((srb->acb != acb) || (srb->srb_state != ARCMSR_SRB_START)) {
			if(srb->srb_state == ARCMSR_SRB_ABORTED) {
				printf("arcmsr%d: scsi id=%d lun=%jx srb='%p'poll command abort successfully \n"
						, acb->pci_unit, srb->pccb->ccb_h.target_id, (uintmax_t)srb->pccb->ccb_h.target_lun, srb);
				srb->pccb->ccb_h.status |= CAM_REQ_ABORTED;
				arcmsr_srb_complete(srb, 1);
				continue;
			}
			printf("arcmsr%d: polling get an illegal srb command done srb='%p'srboutstandingcount=%d \n"
					, acb->pci_unit, srb, acb->srboutstandingcount);
			continue;
		}
		arcmsr_report_srb_state(acb, srb, error);
	}	/*drain reply FIFO*/
}