#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {int id; scalar_t__ size; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_dcache_wb_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_icache_sync_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_wb_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcache_wb_pou (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icache_inv_all () ; 

int
elf_cpu_load_file(linker_file_t lf)
{

	/*
	 * The pmap code does not do an icache sync upon establishing executable
	 * mappings in the kernel pmap.  It's an optimization based on the fact
	 * that kernel memory allocations always have EXECUTABLE protection even
	 * when the memory isn't going to hold executable code.  The only time
	 * kernel memory holding instructions does need a sync is after loading
	 * a kernel module, and that's when this function gets called.
	 *
	 * This syncs data and instruction caches after loading a module.  We
	 * don't worry about the kernel itself (lf->id is 1) as locore.S did
	 * that on entry.  Even if data cache maintenance was done by IO code,
	 * the relocation fixup process creates dirty cache entries that we must
	 * write back before doing icache sync. The instruction cache sync also
	 * invalidates the branch predictor cache on platforms that have one.
	 */
	if (lf->id == 1)
		return (0);
#if __ARM_ARCH >= 6
	dcache_wb_pou((vm_offset_t)lf->address, (vm_size_t)lf->size);
	icache_inv_all();
#else
	cpu_dcache_wb_range((vm_offset_t)lf->address, (vm_size_t)lf->size);
	cpu_l2cache_wb_range((vm_offset_t)lf->address, (vm_size_t)lf->size);
	cpu_icache_sync_range((vm_offset_t)lf->address, (vm_size_t)lf->size);
#endif
	return (0);
}