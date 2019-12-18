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
struct AdapterControlBlock {int in_doorbell; } ;

/* Variables and functions */
 int ARCMSR_HBEMU_IOP2DRV_DATA_READ_OK ; 
 int ARCMSR_HBEMU_IOP2DRV_DATA_WRITE_OK ; 
 int ARCMSR_HBEMU_IOP2DRV_MESSAGE_CMD_DONE ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hbe_message_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop2drv_data_read_handle (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop2drv_data_wrote_handle (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  host_int_status ; 
 int /*<<< orphan*/  iobound_doorbell ; 

__attribute__((used)) static void arcmsr_hbe_doorbell_isr(struct AdapterControlBlock *acb)
{
	u_int32_t doorbell_status, in_doorbell;
	
	/*
	*******************************************************************
	**  Maybe here we need to check wrqbuffer_lock is lock or not
	**  DOORBELL: din! don! 
	**  check if there are any mail need to pack from firmware
	*******************************************************************
	*/
	in_doorbell = CHIP_REG_READ32(HBE_MessageUnit, 0, iobound_doorbell);
	CHIP_REG_WRITE32(HBE_MessageUnit, 0, host_int_status, 0); /* clear doorbell interrupt */
	doorbell_status = in_doorbell ^ acb->in_doorbell;
	if(doorbell_status & ARCMSR_HBEMU_IOP2DRV_DATA_WRITE_OK) {
		arcmsr_iop2drv_data_wrote_handle(acb);
	}
	if(doorbell_status & ARCMSR_HBEMU_IOP2DRV_DATA_READ_OK) {
		arcmsr_iop2drv_data_read_handle(acb);
	}
	if(doorbell_status & ARCMSR_HBEMU_IOP2DRV_MESSAGE_CMD_DONE) {
		arcmsr_hbe_message_isr(acb);    /* messenger of "driver to iop commands" */
	}
	acb->in_doorbell = in_doorbell;
}