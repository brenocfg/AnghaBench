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
struct TYPE_2__ {int target_id; scalar_t__ target_lun; scalar_t__ arcmsr_ccbacb_ptr; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct CommandControlBlock {scalar_t__ srb_state; union ccb* pccb; } ;
struct AdapterControlBlock {scalar_t__ srboutstandingcount; int pci_unit; struct CommandControlBlock** psrb_pool; int /*<<< orphan*/  num_aborts; } ;

/* Variables and functions */
 int ARCMSR_MAX_FREESRB_NUM ; 
 scalar_t__ ARCMSR_SRB_ABORTED ; 
 scalar_t__ ARCMSR_SRB_START ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arcmsr_disable_allintr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_enable_allintr (struct AdapterControlBlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_polling_srbdone (struct AdapterControlBlock*,struct CommandControlBlock*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ,struct CommandControlBlock*) ; 

__attribute__((used)) static u_int8_t arcmsr_seek_cmd2abort(union ccb *abortccb)
{
	struct CommandControlBlock *srb;
	struct AdapterControlBlock *acb = (struct AdapterControlBlock *) abortccb->ccb_h.arcmsr_ccbacb_ptr;
	u_int32_t intmask_org;
	int i = 0;

	acb->num_aborts++;
	/*
	***************************************************************************
	** It is the upper layer do abort command this lock just prior to calling us.
	** First determine if we currently own this command.
	** Start by searching the device queue. If not found
	** at all, and the system wanted us to just abort the
	** command return success.
	***************************************************************************
	*/
	if(acb->srboutstandingcount != 0) {
		/* disable all outbound interrupt */
		intmask_org = arcmsr_disable_allintr(acb);
		for(i=0; i < ARCMSR_MAX_FREESRB_NUM; i++) {
			srb = acb->psrb_pool[i];
			if(srb->srb_state == ARCMSR_SRB_START) {
				if(srb->pccb == abortccb) {
					srb->srb_state = ARCMSR_SRB_ABORTED;
					printf("arcmsr%d:scsi id=%d lun=%jx abort srb '%p'"
						"outstanding command \n"
						, acb->pci_unit, abortccb->ccb_h.target_id
						, (uintmax_t)abortccb->ccb_h.target_lun, srb);
					arcmsr_polling_srbdone(acb, srb);
					/* enable outbound Post Queue, outbound doorbell Interrupt */
					arcmsr_enable_allintr(acb, intmask_org);
					return (TRUE);
				}
			}
		}
		/* enable outbound Post Queue, outbound doorbell Interrupt */
		arcmsr_enable_allintr(acb, intmask_org);
	}
	return(FALSE);
}