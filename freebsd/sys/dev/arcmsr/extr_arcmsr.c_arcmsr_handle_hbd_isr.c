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
 int ARCMSR_HBDMU_ALL_INT_DISABLE ; 
 int ARCMSR_HBDMU_ALL_INT_ENABLE ; 
 int ARCMSR_HBDMU_OUTBOUND_DOORBELL_INT ; 
 int ARCMSR_HBDMU_OUTBOUND_INT ; 
 int ARCMSR_HBDMU_OUTBOUND_POSTQUEUE_INT ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hbd_doorbell_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbd_postqueue_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  host_int_status ; 
 int /*<<< orphan*/  pcief0_int_enable ; 

__attribute__((used)) static void arcmsr_handle_hbd_isr( struct AdapterControlBlock *acb)
{
	u_int32_t host_interrupt_status;
	u_int32_t intmask_org;
	/*
	*********************************************
	**   check outbound intstatus 
	*********************************************
	*/
	host_interrupt_status = CHIP_REG_READ32(HBD_MessageUnit, 0, host_int_status) & acb->outbound_int_enable;
	if(!(host_interrupt_status & ARCMSR_HBDMU_OUTBOUND_INT)) {
		/*it must be share irq*/
		return;
	}
	/* disable outbound interrupt */
	intmask_org = CHIP_REG_READ32(HBD_MessageUnit, 0, pcief0_int_enable)	; /* disable outbound message0 int */
	CHIP_REG_WRITE32(HBD_MessageUnit, 0, pcief0_int_enable, ARCMSR_HBDMU_ALL_INT_DISABLE);
	/* MU doorbell interrupts*/
	if(host_interrupt_status & ARCMSR_HBDMU_OUTBOUND_DOORBELL_INT) {
		arcmsr_hbd_doorbell_isr(acb);
	}
	/* MU post queue interrupts*/
	if(host_interrupt_status & ARCMSR_HBDMU_OUTBOUND_POSTQUEUE_INT) {
		arcmsr_hbd_postqueue_isr(acb);
	}
	/* enable all outbound interrupt */
	CHIP_REG_WRITE32(HBD_MessageUnit, 0, pcief0_int_enable, intmask_org | ARCMSR_HBDMU_ALL_INT_ENABLE);
//	CHIP_REG_READ32(HBD_MessageUnit, 0, pcief0_int_enable);
}