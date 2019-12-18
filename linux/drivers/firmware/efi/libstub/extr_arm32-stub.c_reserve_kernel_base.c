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
typedef  unsigned long u64 ;
struct efi_boot_memmap {unsigned long* map_size; unsigned long* desc_size; unsigned long* buff_size; int /*<<< orphan*/ * key_ptr; int /*<<< orphan*/ * desc_ver; TYPE_1__** map; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  unsigned long efi_physical_addr_t ;
struct TYPE_3__ {unsigned long phys_addr; unsigned long num_pages; int type; } ;
typedef  TYPE_1__ efi_memory_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ALLOCATE_ADDRESS ; 
 int /*<<< orphan*/  EFI_ALLOCATE_MAX_ADDRESS ; 
#define  EFI_BOOT_SERVICES_CODE 132 
#define  EFI_BOOT_SERVICES_DATA 131 
#define  EFI_CONVENTIONAL_MEMORY 130 
#define  EFI_LOADER_CODE 129 
#define  EFI_LOADER_DATA 128 
 scalar_t__ EFI_OUT_OF_RESOURCES ; 
 unsigned long EFI_PAGE_SIZE ; 
 scalar_t__ EFI_SUCCESS ; 
 unsigned long MAX_UNCOMP_KERNEL_SIZE ; 
 int /*<<< orphan*/  allocate_pages ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,TYPE_1__*,...) ; 
 scalar_t__ efi_get_memory_map (int /*<<< orphan*/ *,struct efi_boot_memmap*) ; 
 int /*<<< orphan*/  free_pool ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static efi_status_t reserve_kernel_base(efi_system_table_t *sys_table_arg,
					unsigned long dram_base,
					unsigned long *reserve_addr,
					unsigned long *reserve_size)
{
	efi_physical_addr_t alloc_addr;
	efi_memory_desc_t *memory_map;
	unsigned long nr_pages, map_size, desc_size, buff_size;
	efi_status_t status;
	unsigned long l;

	struct efi_boot_memmap map = {
		.map		= &memory_map,
		.map_size	= &map_size,
		.desc_size	= &desc_size,
		.desc_ver	= NULL,
		.key_ptr	= NULL,
		.buff_size	= &buff_size,
	};

	/*
	 * Reserve memory for the uncompressed kernel image. This is
	 * all that prevents any future allocations from conflicting
	 * with the kernel. Since we can't tell from the compressed
	 * image how much DRAM the kernel actually uses (due to BSS
	 * size uncertainty) we allocate the maximum possible size.
	 * Do this very early, as prints can cause memory allocations
	 * that may conflict with this.
	 */
	alloc_addr = dram_base + MAX_UNCOMP_KERNEL_SIZE;
	nr_pages = MAX_UNCOMP_KERNEL_SIZE / EFI_PAGE_SIZE;
	status = efi_call_early(allocate_pages, EFI_ALLOCATE_MAX_ADDRESS,
				EFI_BOOT_SERVICES_DATA, nr_pages, &alloc_addr);
	if (status == EFI_SUCCESS) {
		if (alloc_addr == dram_base) {
			*reserve_addr = alloc_addr;
			*reserve_size = MAX_UNCOMP_KERNEL_SIZE;
			return EFI_SUCCESS;
		}
		/*
		 * If we end up here, the allocation succeeded but starts below
		 * dram_base. This can only occur if the real base of DRAM is
		 * not a multiple of 128 MB, in which case dram_base will have
		 * been rounded up. Since this implies that a part of the region
		 * was already occupied, we need to fall through to the code
		 * below to ensure that the existing allocations don't conflict.
		 * For this reason, we use EFI_BOOT_SERVICES_DATA above and not
		 * EFI_LOADER_DATA, which we wouldn't able to distinguish from
		 * allocations that we want to disallow.
		 */
	}

	/*
	 * If the allocation above failed, we may still be able to proceed:
	 * if the only allocations in the region are of types that will be
	 * released to the OS after ExitBootServices(), the decompressor can
	 * safely overwrite them.
	 */
	status = efi_get_memory_map(sys_table_arg, &map);
	if (status != EFI_SUCCESS) {
		pr_efi_err(sys_table_arg,
			   "reserve_kernel_base(): Unable to retrieve memory map.\n");
		return status;
	}

	for (l = 0; l < map_size; l += desc_size) {
		efi_memory_desc_t *desc;
		u64 start, end;

		desc = (void *)memory_map + l;
		start = desc->phys_addr;
		end = start + desc->num_pages * EFI_PAGE_SIZE;

		/* Skip if entry does not intersect with region */
		if (start >= dram_base + MAX_UNCOMP_KERNEL_SIZE ||
		    end <= dram_base)
			continue;

		switch (desc->type) {
		case EFI_BOOT_SERVICES_CODE:
		case EFI_BOOT_SERVICES_DATA:
			/* Ignore types that are released to the OS anyway */
			continue;

		case EFI_CONVENTIONAL_MEMORY:
			/*
			 * Reserve the intersection between this entry and the
			 * region.
			 */
			start = max(start, (u64)dram_base);
			end = min(end, (u64)dram_base + MAX_UNCOMP_KERNEL_SIZE);

			status = efi_call_early(allocate_pages,
						EFI_ALLOCATE_ADDRESS,
						EFI_LOADER_DATA,
						(end - start) / EFI_PAGE_SIZE,
						&start);
			if (status != EFI_SUCCESS) {
				pr_efi_err(sys_table_arg,
					"reserve_kernel_base(): alloc failed.\n");
				goto out;
			}
			break;

		case EFI_LOADER_CODE:
		case EFI_LOADER_DATA:
			/*
			 * These regions may be released and reallocated for
			 * another purpose (including EFI_RUNTIME_SERVICE_DATA)
			 * at any time during the execution of the OS loader,
			 * so we cannot consider them as safe.
			 */
		default:
			/*
			 * Treat any other allocation in the region as unsafe */
			status = EFI_OUT_OF_RESOURCES;
			goto out;
		}
	}

	status = EFI_SUCCESS;
out:
	efi_call_early(free_pool, memory_map);
	return status;
}