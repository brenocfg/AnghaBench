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

/* Variables and functions */
 int /*<<< orphan*/  PHYS_OFFSET ; 
 int /*<<< orphan*/  VA_BITS ; 
 int /*<<< orphan*/  VMCOREINFO_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kaslr_offset () ; 
 int /*<<< orphan*/  kimage_voffset ; 
 int /*<<< orphan*/  vmcoreinfo_append_str (char*,int /*<<< orphan*/ ) ; 

void arch_crash_save_vmcoreinfo(void)
{
	VMCOREINFO_NUMBER(VA_BITS);
	/* Please note VMCOREINFO_NUMBER() uses "%d", not "%x" */
	vmcoreinfo_append_str("NUMBER(kimage_voffset)=0x%llx\n",
						kimage_voffset);
	vmcoreinfo_append_str("NUMBER(PHYS_OFFSET)=0x%llx\n",
						PHYS_OFFSET);
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n", kaslr_offset());
}