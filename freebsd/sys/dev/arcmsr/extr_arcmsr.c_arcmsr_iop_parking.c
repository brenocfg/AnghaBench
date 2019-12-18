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
struct AdapterControlBlock {int acb_flags; } ;

/* Variables and functions */
 int ACB_F_MSG_START_BGRB ; 
 int /*<<< orphan*/  arcmsr_disable_allintr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_enable_allintr (struct AdapterControlBlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcmsr_flush_adapter_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_stop_adapter_bgrb (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_iop_parking(struct AdapterControlBlock *acb)
{
	u_int32_t intmask_org;

	if(acb != NULL) {
		/* stop adapter background rebuild */
		if(acb->acb_flags & ACB_F_MSG_START_BGRB) {
			intmask_org = arcmsr_disable_allintr(acb);
			arcmsr_stop_adapter_bgrb(acb);
			arcmsr_flush_adapter_cache(acb);
			arcmsr_enable_allintr(acb, intmask_org);
		}
	}
}