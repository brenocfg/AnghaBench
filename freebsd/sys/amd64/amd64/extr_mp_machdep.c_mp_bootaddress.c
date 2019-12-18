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
typedef  scalar_t__ vm_paddr_t ;

/* Variables and functions */
 scalar_t__ AP_BOOTPT_SZ ; 
 int /*<<< orphan*/  alloc_ap_trampoline (scalar_t__*,unsigned int*) ; 
 scalar_t__ boot_address ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  is_kernel_paddr (scalar_t__) ; 
 scalar_t__ is_mpboot_good (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int mptramp_pagetables ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

void
mp_bootaddress(vm_paddr_t *physmap, unsigned int *physmap_idx)
{
	vm_paddr_t start, end;
	unsigned int i;
	bool allocated;

	alloc_ap_trampoline(physmap, physmap_idx);

	/*
	 * Find a memory region big enough below the 4GB boundary to
	 * store the initial page tables.  Region must be mapped by
	 * the direct map.
	 *
	 * Note that it needs to be aligned to a page boundary.
	 */
	allocated = false;
	for (i = *physmap_idx; i <= *physmap_idx; i -= 2) {
		/*
		 * First, try to chomp at the start of the physmap region.
		 * Kernel binary might claim it already.
		 */
		start = round_page(physmap[i]);
		end = start + AP_BOOTPT_SZ;
		if (start < end && end <= physmap[i + 1] &&
		    is_mpboot_good(start, end) &&
		    !is_kernel_paddr(start) && !is_kernel_paddr(end - 1)) {
			allocated = true;
			physmap[i] = end;
			break;
		}

		/*
		 * Second, try to chomp at the end.  Again, check
		 * against kernel.
		 */
		end = trunc_page(physmap[i + 1]);
		start = end - AP_BOOTPT_SZ;
		if (start < end && start >= physmap[i] &&
		    is_mpboot_good(start, end) &&
		    !is_kernel_paddr(start) && !is_kernel_paddr(end - 1)) {
			allocated = true;
			physmap[i + 1] = start;
			break;
		}
	}
	if (allocated) {
		mptramp_pagetables = start;
		if (physmap[i] == physmap[i + 1] && *physmap_idx != 0) {
			memmove(&physmap[i], &physmap[i + 2],
			    sizeof(*physmap) * (*physmap_idx - i + 2));
			*physmap_idx -= 2;
		}
	} else {
		mptramp_pagetables = trunc_page(boot_address) - AP_BOOTPT_SZ;
		if (bootverbose)
			printf(
"Cannot find enough space for the initial AP page tables, placing them at %#x",
			    mptramp_pagetables);
	}
}