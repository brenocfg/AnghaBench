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
struct HBB_MessageUnit {int /*<<< orphan*/  drv2iop_doorbell; int /*<<< orphan*/  iop2drv_doorbell; } ;
struct AdapterControlBlock {int outbound_int_enable; scalar_t__ pmu; } ;

/* Variables and functions */
 int ARCMSR_DRV2IOP_END_OF_INTERRUPT ; 
 int ARCMSR_IOP2DRV_CDB_DONE ; 
 int ARCMSR_IOP2DRV_DATA_READ_OK ; 
 int ARCMSR_IOP2DRV_DATA_WRITE_OK ; 
 int ARCMSR_IOP2DRV_MESSAGE_CMD_DONE ; 
 int READ_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arcmsr_hbb_message_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbb_postqueue_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop2drv_data_read_handle (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop2drv_data_wrote_handle (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_handle_hbb_isr( struct AdapterControlBlock *acb)
{
	u_int32_t outbound_doorbell;
	struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
	/*
	*********************************************
	**   check outbound intstatus 
	*********************************************
	*/
	outbound_doorbell = READ_CHIP_REG32(0, phbbmu->iop2drv_doorbell) & acb->outbound_int_enable;
	if(!outbound_doorbell) {
		/*it must be share irq*/
		return;
	}
	WRITE_CHIP_REG32(0, phbbmu->iop2drv_doorbell, ~outbound_doorbell); /* clear doorbell interrupt */
	READ_CHIP_REG32(0, phbbmu->iop2drv_doorbell);
	WRITE_CHIP_REG32(0, phbbmu->drv2iop_doorbell, ARCMSR_DRV2IOP_END_OF_INTERRUPT);
	/* MU ioctl transfer doorbell interrupts*/
	if(outbound_doorbell & ARCMSR_IOP2DRV_DATA_WRITE_OK) {
		arcmsr_iop2drv_data_wrote_handle(acb);
	}
	if(outbound_doorbell & ARCMSR_IOP2DRV_DATA_READ_OK) {
		arcmsr_iop2drv_data_read_handle(acb);
	}
	/* MU post queue interrupts*/
	if(outbound_doorbell & ARCMSR_IOP2DRV_CDB_DONE) {
		arcmsr_hbb_postqueue_isr(acb);
	}
	if(outbound_doorbell & ARCMSR_IOP2DRV_MESSAGE_CMD_DONE) {
		arcmsr_hbb_message_isr(acb);
	}
}