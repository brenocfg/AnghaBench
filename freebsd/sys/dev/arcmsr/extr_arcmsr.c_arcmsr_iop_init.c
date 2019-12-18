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
typedef  int /*<<< orphan*/  u_int32_t ;
struct AdapterControlBlock {int /*<<< orphan*/  acb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_IOP_INITED ; 
 int /*<<< orphan*/  arcmsr_clear_doorbell_queue_buffer (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_disable_allintr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_enable_allintr (struct AdapterControlBlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_enable_eoi_mode (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_get_firmware_spec (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_confirm (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_start_adapter_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_wait_firmware_ready (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_iop_init(struct AdapterControlBlock *acb)
{
	u_int32_t intmask_org;

	/* disable all outbound interrupt */
	intmask_org = arcmsr_disable_allintr(acb);
	arcmsr_wait_firmware_ready(acb);
	arcmsr_iop_confirm(acb);
	arcmsr_get_firmware_spec(acb);
	/*start background rebuild*/
	arcmsr_start_adapter_bgrb(acb);
	/* empty doorbell Qbuffer if door bell ringed */
	arcmsr_clear_doorbell_queue_buffer(acb);
	arcmsr_enable_eoi_mode(acb);
	/* enable outbound Post Queue, outbound doorbell Interrupt */
	arcmsr_enable_allintr(acb, intmask_org);
	acb->acb_flags |= ACB_F_IOP_INITED;
}