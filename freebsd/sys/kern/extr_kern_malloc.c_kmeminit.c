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
typedef  int u_long ;
struct TYPE_2__ {int v_page_count; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int VM_KMEM_SIZE ; 
 int VM_KMEM_SIZE_MAX ; 
 int VM_KMEM_SIZE_MIN ; 
 int VM_KMEM_SIZE_SCALE ; 
 int /*<<< orphan*/  kernel_arena ; 
 int /*<<< orphan*/  kernel_map ; 
 int kmem_zmax ; 
 int memguard_fudge (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memguard_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int round_page (int) ; 
 int /*<<< orphan*/  uma_set_limit (int) ; 
 TYPE_1__ vm_cnt ; 
 int vm_kmem_size ; 
 int vm_kmem_size_max ; 
 int vm_kmem_size_min ; 
 int vm_kmem_size_scale ; 

void
kmeminit(void)
{
	u_long mem_size;
	u_long tmp;

#ifdef VM_KMEM_SIZE
	if (vm_kmem_size == 0)
		vm_kmem_size = VM_KMEM_SIZE;
#endif
#ifdef VM_KMEM_SIZE_MIN
	if (vm_kmem_size_min == 0)
		vm_kmem_size_min = VM_KMEM_SIZE_MIN;
#endif
#ifdef VM_KMEM_SIZE_MAX
	if (vm_kmem_size_max == 0)
		vm_kmem_size_max = VM_KMEM_SIZE_MAX;
#endif
	/*
	 * Calculate the amount of kernel virtual address (KVA) space that is
	 * preallocated to the kmem arena.  In order to support a wide range
	 * of machines, it is a function of the physical memory size,
	 * specifically,
	 *
	 *	min(max(physical memory size / VM_KMEM_SIZE_SCALE,
	 *	    VM_KMEM_SIZE_MIN), VM_KMEM_SIZE_MAX)
	 *
	 * Every architecture must define an integral value for
	 * VM_KMEM_SIZE_SCALE.  However, the definitions of VM_KMEM_SIZE_MIN
	 * and VM_KMEM_SIZE_MAX, which represent respectively the floor and
	 * ceiling on this preallocation, are optional.  Typically,
	 * VM_KMEM_SIZE_MAX is itself a function of the available KVA space on
	 * a given architecture.
	 */
	mem_size = vm_cnt.v_page_count;
	if (mem_size <= 32768) /* delphij XXX 128MB */
		kmem_zmax = PAGE_SIZE;

	if (vm_kmem_size_scale < 1)
		vm_kmem_size_scale = VM_KMEM_SIZE_SCALE;

	/*
	 * Check if we should use defaults for the "vm_kmem_size"
	 * variable:
	 */
	if (vm_kmem_size == 0) {
		vm_kmem_size = mem_size / vm_kmem_size_scale;
		vm_kmem_size = vm_kmem_size * PAGE_SIZE < vm_kmem_size ?
		    vm_kmem_size_max : vm_kmem_size * PAGE_SIZE;
		if (vm_kmem_size_min > 0 && vm_kmem_size < vm_kmem_size_min)
			vm_kmem_size = vm_kmem_size_min;
		if (vm_kmem_size_max > 0 && vm_kmem_size >= vm_kmem_size_max)
			vm_kmem_size = vm_kmem_size_max;
	}
	if (vm_kmem_size == 0)
		panic("Tune VM_KMEM_SIZE_* for the platform");

	/*
	 * The amount of KVA space that is preallocated to the
	 * kmem arena can be set statically at compile-time or manually
	 * through the kernel environment.  However, it is still limited to
	 * twice the physical memory size, which has been sufficient to handle
	 * the most severe cases of external fragmentation in the kmem arena. 
	 */
	if (vm_kmem_size / 2 / PAGE_SIZE > mem_size)
		vm_kmem_size = 2 * mem_size * PAGE_SIZE;

	vm_kmem_size = round_page(vm_kmem_size);
#ifdef DEBUG_MEMGUARD
	tmp = memguard_fudge(vm_kmem_size, kernel_map);
#else
	tmp = vm_kmem_size;
#endif
	uma_set_limit(tmp);

#ifdef DEBUG_MEMGUARD
	/*
	 * Initialize MemGuard if support compiled in.  MemGuard is a
	 * replacement allocator used for detecting tamper-after-free
	 * scenarios as they occur.  It is only used for debugging.
	 */
	memguard_init(kernel_arena);
#endif
}