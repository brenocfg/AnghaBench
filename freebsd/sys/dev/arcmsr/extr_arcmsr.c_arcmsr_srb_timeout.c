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
typedef  int u_int8_t ;
struct CommandControlBlock {scalar_t__ srb_state; TYPE_2__* pccb; struct AdapterControlBlock* acb; } ;
struct AdapterControlBlock {int pci_unit; int /*<<< orphan*/  isr_lock; } ;
struct TYPE_3__ {int target_id; int target_lun; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; int /*<<< orphan*/  csio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARCMSR_SRB_START ; 
 scalar_t__ ARCMSR_SRB_TIMEOUT ; 
 int /*<<< orphan*/  CAM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  arcmsr_dump_data (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_srb_complete (struct CommandControlBlock*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,struct CommandControlBlock*) ; 
 int* scsiio_cdb_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void	arcmsr_srb_timeout(void *arg)
{
	struct CommandControlBlock *srb = (struct CommandControlBlock *)arg;
	struct AdapterControlBlock *acb;
	int target, lun;
	u_int8_t cmd;

	target = srb->pccb->ccb_h.target_id;
	lun = srb->pccb->ccb_h.target_lun;
	acb = srb->acb;
	ARCMSR_LOCK_ACQUIRE(&acb->isr_lock);
	if(srb->srb_state == ARCMSR_SRB_START)
	{
		cmd = scsiio_cdb_ptr(&srb->pccb->csio)[0];
		srb->srb_state = ARCMSR_SRB_TIMEOUT;
		srb->pccb->ccb_h.status |= CAM_CMD_TIMEOUT;
		arcmsr_srb_complete(srb, 1);
		printf("arcmsr%d: scsi id %d lun %d cmd=0x%x srb='%p' ccb command time out!\n",
				 acb->pci_unit, target, lun, cmd, srb);
	}
	ARCMSR_LOCK_RELEASE(&acb->isr_lock);
#ifdef ARCMSR_DEBUG1
	arcmsr_dump_data(acb);
#endif
}