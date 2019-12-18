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
struct AdapterControlBlock {int outbound_int_enable; } ;

/* Variables and functions */
 int ARCMSR_MU_OUTBOUND_DOORBELL_INT ; 
 int ARCMSR_MU_OUTBOUND_MESSAGE0_INT ; 
 int ARCMSR_MU_OUTBOUND_POSTQUEUE_INT ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hba_doorbell_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hba_message_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hba_postqueue_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  outbound_intstatus ; 

__attribute__((used)) static void arcmsr_handle_hba_isr( struct AdapterControlBlock *acb)
{
	u_int32_t outbound_intStatus;
	/*
	*********************************************
	**   check outbound intstatus 
	*********************************************
	*/
	outbound_intStatus = CHIP_REG_READ32(HBA_MessageUnit, 0, outbound_intstatus) & acb->outbound_int_enable;
	if(!outbound_intStatus) {
		/*it must be share irq*/
		return;
	}
	CHIP_REG_WRITE32(HBA_MessageUnit, 0, outbound_intstatus, outbound_intStatus); /*clear interrupt*/
	/* MU doorbell interrupts*/
	if(outbound_intStatus & ARCMSR_MU_OUTBOUND_DOORBELL_INT) {
		arcmsr_hba_doorbell_isr(acb);
	}
	/* MU post queue interrupts*/
	if(outbound_intStatus & ARCMSR_MU_OUTBOUND_POSTQUEUE_INT) {
		arcmsr_hba_postqueue_isr(acb);
	}
	if(outbound_intStatus & ARCMSR_MU_OUTBOUND_MESSAGE0_INT) {
		arcmsr_hba_message_isr(acb);
	}
}