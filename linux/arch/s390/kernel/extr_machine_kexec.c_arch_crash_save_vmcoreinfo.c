#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vmcore_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_CPUS ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  VMCOREINFO_LENGTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_SYMBOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __edma ; 
 int /*<<< orphan*/  __sdma ; 
 int /*<<< orphan*/  high_memory ; 
 int /*<<< orphan*/  kaslr_offset () ; 
 int /*<<< orphan*/  lowcore_ptr ; 
 int /*<<< orphan*/  mem_assign_absolute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_vmcoreinfo_note () ; 
 int /*<<< orphan*/  vmcoreinfo_append_str (char*,int /*<<< orphan*/ ) ; 

void arch_crash_save_vmcoreinfo(void)
{
	VMCOREINFO_SYMBOL(lowcore_ptr);
	VMCOREINFO_SYMBOL(high_memory);
	VMCOREINFO_LENGTH(lowcore_ptr, NR_CPUS);
	mem_assign_absolute(S390_lowcore.vmcore_info, paddr_vmcoreinfo_note());
	vmcoreinfo_append_str("SDMA=%lx\n", __sdma);
	vmcoreinfo_append_str("EDMA=%lx\n", __edma);
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n", kaslr_offset());
}