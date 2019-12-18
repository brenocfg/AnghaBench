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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct CommandControlBlock {scalar_t__ srb_state; TYPE_2__* pccb; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {int outbound_int_enable; int pci_unit; int srboutstandingcount; scalar_t__ vir2phy_offset; int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; } ;
struct TYPE_3__ {int target_id; int /*<<< orphan*/  status; scalar_t__ target_lun; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int ARCMSR_SRBREPLY_FLAG_ERROR_MODE0 ; 
 scalar_t__ ARCMSR_SRB_ABORTED ; 
 scalar_t__ ARCMSR_SRB_START ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  arcmsr_report_srb_state (struct AdapterControlBlock*,struct CommandControlBlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_srb_complete (struct CommandControlBlock*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int outbound_queueport ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void arcmsr_polling_hba_srbdone(struct AdapterControlBlock *acb, struct CommandControlBlock *poll_srb)
{
	struct CommandControlBlock *srb;
	u_int32_t flag_srb, outbound_intstatus, poll_srb_done=0, poll_count=0;
	u_int16_t	error;

polling_ccb_retry:
	poll_count++;
	outbound_intstatus=CHIP_REG_READ32(HBA_MessageUnit, 0, outbound_intstatus) & acb->outbound_int_enable;
	CHIP_REG_WRITE32(HBA_MessageUnit, 0, outbound_intstatus, outbound_intstatus);	/*clear interrupt*/
	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	while(1) {
		if((flag_srb = CHIP_REG_READ32(HBA_MessageUnit, 
			0, outbound_queueport)) == 0xFFFFFFFF) {
			if(poll_srb_done) {
				break;/*chip FIFO no ccb for completion already*/
			} else {
				UDELAY(25000);
				if ((poll_count > 100) && (poll_srb != NULL)) {
					break;
				}
				goto polling_ccb_retry;
			}
		}
		/* check if command done with no error*/
		srb = (struct CommandControlBlock *)
			(acb->vir2phy_offset+(flag_srb << 5));/*frame must be 32 bytes aligned*/
		error = (flag_srb & ARCMSR_SRBREPLY_FLAG_ERROR_MODE0)?TRUE:FALSE;
		poll_srb_done = (srb == poll_srb) ? 1:0;
		if((srb->acb != acb) || (srb->srb_state != ARCMSR_SRB_START)) {
			if(srb->srb_state == ARCMSR_SRB_ABORTED) {
				printf("arcmsr%d: scsi id=%d lun=%jx srb='%p'"
					"poll command abort successfully \n"
					, acb->pci_unit
					, srb->pccb->ccb_h.target_id
					, (uintmax_t)srb->pccb->ccb_h.target_lun, srb);
				srb->pccb->ccb_h.status |= CAM_REQ_ABORTED;
				arcmsr_srb_complete(srb, 1);
				continue;
			}
			printf("arcmsr%d: polling get an illegal srb command done srb='%p'"
				"srboutstandingcount=%d \n"
				, acb->pci_unit
				, srb, acb->srboutstandingcount);
			continue;
		}
		arcmsr_report_srb_state(acb, srb, error);
	}	/*drain reply FIFO*/
}