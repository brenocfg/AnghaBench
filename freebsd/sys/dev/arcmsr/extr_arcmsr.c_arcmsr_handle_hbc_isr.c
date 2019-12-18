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
 int ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR ; 
 int ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR ; 
 int CHIP_REG_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  arcmsr_hbc_doorbell_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbc_postqueue_isr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  host_int_status ; 

__attribute__((used)) static void arcmsr_handle_hbc_isr( struct AdapterControlBlock *acb)
{
	u_int32_t host_interrupt_status;
	/*
	*********************************************
	**   check outbound intstatus 
	*********************************************
	*/
	host_interrupt_status = CHIP_REG_READ32(HBC_MessageUnit, 0, host_int_status) &
		(ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR |
		ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR);
	if(!host_interrupt_status) {
		/*it must be share irq*/
		return;
	}
	do {
		/* MU doorbell interrupts*/
		if(host_interrupt_status & ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR) {
			arcmsr_hbc_doorbell_isr(acb);
		}
		/* MU post queue interrupts*/
		if(host_interrupt_status & ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR) {
			arcmsr_hbc_postqueue_isr(acb);
		}
		host_interrupt_status = CHIP_REG_READ32(HBC_MessageUnit, 0, host_int_status);
	} while (host_interrupt_status & (ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR | ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR));
}