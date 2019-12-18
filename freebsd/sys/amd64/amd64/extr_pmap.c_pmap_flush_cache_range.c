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

/* Variables and functions */
 int CPUID_STDEXT_CLWB ; 
 int /*<<< orphan*/  atomic_thread_fence_seq_cst () ; 
 int /*<<< orphan*/  clwb (scalar_t__) ; 
 scalar_t__ cpu_clflush_line_size ; 
 int cpu_stdext_feature ; 
 scalar_t__ lapic_paddr ; 
 int /*<<< orphan*/  pmap_force_invalidate_cache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_invalidate_cache_range_check_align (scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_kextract (scalar_t__) ; 

void
pmap_flush_cache_range(vm_offset_t sva, vm_offset_t eva)
{

	pmap_invalidate_cache_range_check_align(sva, eva);

	if ((cpu_stdext_feature & CPUID_STDEXT_CLWB) == 0) {
		pmap_force_invalidate_cache_range(sva, eva);
		return;
	}

	/* See comment in pmap_force_invalidate_cache_range(). */
	if (pmap_kextract(sva) == lapic_paddr)
		return;

	atomic_thread_fence_seq_cst();
	for (; sva < eva; sva += cpu_clflush_line_size)
		clwb(sva);
	atomic_thread_fence_seq_cst();
}