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
typedef  int /*<<< orphan*/  u_int32_t ;
struct CommandControlBlock {scalar_t__ srb_state; TYPE_2__* pccb; } ;
struct AdapterControlBlock {int pci_unit; struct CommandControlBlock** psrb_pool; } ;
struct TYPE_3__ {int target_id; int target_lun; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int ARCMSR_MAX_FREESRB_NUM ; 
 scalar_t__ ARCMSR_SRB_ABORTED ; 
 scalar_t__ ARCMSR_SRB_START ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  arcmsr_disable_allintr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_enable_allintr (struct AdapterControlBlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_srb_complete (struct CommandControlBlock*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,struct CommandControlBlock*) ; 

__attribute__((used)) static void arcmsr_abort_dr_ccbs(struct AdapterControlBlock *acb, int target, int lun)
{
	struct CommandControlBlock *srb;
	u_int32_t intmask_org;
	int i;

	/* disable all outbound interrupts */
	intmask_org = arcmsr_disable_allintr(acb);
	for (i = 0; i < ARCMSR_MAX_FREESRB_NUM; i++)
	{
		srb = acb->psrb_pool[i];
		if (srb->srb_state == ARCMSR_SRB_START)
		{
			if((target == srb->pccb->ccb_h.target_id) && (lun == srb->pccb->ccb_h.target_lun))
			{
				srb->srb_state = ARCMSR_SRB_ABORTED;
				srb->pccb->ccb_h.status |= CAM_REQ_ABORTED;
				arcmsr_srb_complete(srb, 1);
				printf("arcmsr%d: abort scsi id %d lun %d srb=%p \n", acb->pci_unit, target, lun, srb);
			}
		}
	}
	/* enable outbound Post Queue, outbound doorbell Interrupt */
	arcmsr_enable_allintr(acb, intmask_org);
}