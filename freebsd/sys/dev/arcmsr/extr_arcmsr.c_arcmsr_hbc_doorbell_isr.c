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
typedef  int u_int32_t ;
struct AdapterControlBlock {int dummy; } ;

/* Variables and functions */
 int ARCMSR_HBCMU_IOP2DRV_DATA_READ_OK ; 
 int ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_OK ; 
 int ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hbc_message_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop2drv_data_read_handle (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop2drv_data_wrote_handle (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  outbound_doorbell ; 
 int /*<<< orphan*/  outbound_doorbell_clear ; 

__attribute__((used)) static void arcmsr_hbc_doorbell_isr(struct AdapterControlBlock *acb)
{
	u_int32_t doorbell_status;

	/*
	*******************************************************************
	**  Maybe here we need to check wrqbuffer_lock is lock or not
	**  DOORBELL: din! don! 
	**  check if there are any mail need to pack from firmware
	*******************************************************************
	*/
	doorbell_status = CHIP_REG_READ32(HBC_MessageUnit, 0, outbound_doorbell);
	CHIP_REG_WRITE32(HBC_MessageUnit, 0, outbound_doorbell_clear, doorbell_status); /* clear doorbell interrupt */
	if(doorbell_status & ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_OK) {
		arcmsr_iop2drv_data_wrote_handle(acb);
	}
	if(doorbell_status & ARCMSR_HBCMU_IOP2DRV_DATA_READ_OK) {
		arcmsr_iop2drv_data_read_handle(acb);
	}
	if(doorbell_status & ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE) {
		arcmsr_hbc_message_isr(acb);    /* messenger of "driver to iop commands" */
	}
}