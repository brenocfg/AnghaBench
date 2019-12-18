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
typedef  scalar_t__ vm_offset_t ;
struct pcpu {int pc_next_asid; int pc_asid_generation; struct pcpu* pc_self; } ;

/* Variables and functions */
 scalar_t__ VM_MAX_KERNEL_ADDRESS ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  mips_pcpu_tlb_init (struct pcpu*) ; 
 scalar_t__ pcpup ; 

void
cpu_pcpu_init(struct pcpu *pcpu, int cpuid, size_t size)
{

	pcpu->pc_next_asid = 1;
	pcpu->pc_asid_generation = 1;
	pcpu->pc_self = pcpu;
#ifdef SMP
	if ((vm_offset_t)pcpup >= VM_MIN_KERNEL_ADDRESS &&
	    (vm_offset_t)pcpup <= VM_MAX_KERNEL_ADDRESS) {
		mips_pcpu_tlb_init(pcpu);
	}
#endif
}