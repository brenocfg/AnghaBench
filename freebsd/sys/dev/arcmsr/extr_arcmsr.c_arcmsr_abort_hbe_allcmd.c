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
struct AdapterControlBlock {int pci_unit; int /*<<< orphan*/  out_doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE ; 
 int /*<<< orphan*/  ARCMSR_INBOUND_MESG0_ABORT_CMD ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hbe_wait_msgint_ready (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  inbound_msgaddr0 ; 
 int /*<<< orphan*/  iobound_doorbell ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void arcmsr_abort_hbe_allcmd(struct AdapterControlBlock *acb)
{
	CHIP_REG_WRITE32(HBE_MessageUnit, 0, inbound_msgaddr0, ARCMSR_INBOUND_MESG0_ABORT_CMD);
	acb->out_doorbell ^= ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE;
	CHIP_REG_WRITE32(HBE_MessageUnit, 0, iobound_doorbell, acb->out_doorbell);
	if(!arcmsr_hbe_wait_msgint_ready(acb)) {
		printf("arcmsr%d: wait 'abort all outstanding command' timeout \n", acb->pci_unit);
	}
}