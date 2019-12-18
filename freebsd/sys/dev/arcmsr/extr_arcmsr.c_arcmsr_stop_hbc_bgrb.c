#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct AdapterControlBlock {int pci_unit; int /*<<< orphan*/  acb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_MSG_START_BGRB ; 
 int /*<<< orphan*/  ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE ; 
 int /*<<< orphan*/  ARCMSR_INBOUND_MESG0_STOP_BGRB ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hbc_wait_msgint_ready (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  inbound_doorbell ; 
 int /*<<< orphan*/  inbound_msgaddr0 ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void arcmsr_stop_hbc_bgrb(struct AdapterControlBlock *acb)
{
	acb->acb_flags &= ~ACB_F_MSG_START_BGRB;
	CHIP_REG_WRITE32(HBC_MessageUnit, 0, inbound_msgaddr0, ARCMSR_INBOUND_MESG0_STOP_BGRB);
	CHIP_REG_WRITE32(HBC_MessageUnit, 0, inbound_doorbell,ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE);
	if(!arcmsr_hbc_wait_msgint_ready(acb)) {
		printf("arcmsr%d: wait 'stop adapter background rebulid' timeout \n", acb->pci_unit);
	}
}