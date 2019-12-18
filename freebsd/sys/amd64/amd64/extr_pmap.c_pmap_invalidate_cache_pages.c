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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int CPUID_CLFSH ; 
 int CPUID_STDEXT_CLFLUSHOPT ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 int PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int PMAP_CLFLUSH_THRESHOLD ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_thread_fence_seq_cst () ; 
 int /*<<< orphan*/  clflush (scalar_t__) ; 
 int /*<<< orphan*/  clflushopt (scalar_t__) ; 
 scalar_t__ cpu_clflush_line_size ; 
 int cpu_feature ; 
 int cpu_stdext_feature ; 
 scalar_t__ cpu_vendor_id ; 
 int /*<<< orphan*/  mfence () ; 
 int /*<<< orphan*/  pmap_invalidate_cache () ; 

void
pmap_invalidate_cache_pages(vm_page_t *pages, int count)
{
	vm_offset_t daddr, eva;
	int i;
	bool useclflushopt;

	useclflushopt = (cpu_stdext_feature & CPUID_STDEXT_CLFLUSHOPT) != 0;
	if (count >= PMAP_CLFLUSH_THRESHOLD / PAGE_SIZE ||
	    ((cpu_feature & CPUID_CLFSH) == 0 && !useclflushopt))
		pmap_invalidate_cache();
	else {
		if (useclflushopt)
			atomic_thread_fence_seq_cst();
		else if (cpu_vendor_id != CPU_VENDOR_INTEL)
			mfence();
		for (i = 0; i < count; i++) {
			daddr = PHYS_TO_DMAP(VM_PAGE_TO_PHYS(pages[i]));
			eva = daddr + PAGE_SIZE;
			for (; daddr < eva; daddr += cpu_clflush_line_size) {
				if (useclflushopt)
					clflushopt(daddr);
				else
					clflush(daddr);
			}
		}
		if (useclflushopt)
			atomic_thread_fence_seq_cst();
		else if (cpu_vendor_id != CPU_VENDOR_INTEL)
			mfence();
	}
}