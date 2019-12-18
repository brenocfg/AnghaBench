#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct efi_boot_memmap {unsigned long* map_size; unsigned long* desc_size; unsigned long* buff_size; int /*<<< orphan*/ * key_ptr; int /*<<< orphan*/ * desc_ver; TYPE_1__** map; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_4__ {scalar_t__ type; unsigned long num_pages; unsigned long phys_addr; } ;
typedef  TYPE_1__ efi_memory_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ALLOCATE_ADDRESS ; 
 unsigned long EFI_ALLOC_ALIGN ; 
 scalar_t__ EFI_CONVENTIONAL_MEMORY ; 
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 scalar_t__ EFI_NOT_FOUND ; 
 unsigned long EFI_PAGE_SIZE ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pages ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,TYPE_1__*,...) ; 
 TYPE_1__* efi_early_memdesc_ptr (unsigned long,unsigned long,int) ; 
 scalar_t__ efi_get_memory_map (int /*<<< orphan*/ *,struct efi_boot_memmap*) ; 
 int /*<<< orphan*/  free_pool ; 
 unsigned long round_down (unsigned long,unsigned long) ; 
 unsigned long round_up (unsigned long,unsigned long) ; 

efi_status_t efi_high_alloc(efi_system_table_t *sys_table_arg,
			    unsigned long size, unsigned long align,
			    unsigned long *addr, unsigned long max)
{
	unsigned long map_size, desc_size, buff_size;
	efi_memory_desc_t *map;
	efi_status_t status;
	unsigned long nr_pages;
	u64 max_addr = 0;
	int i;
	struct efi_boot_memmap boot_map;

	boot_map.map =		&map;
	boot_map.map_size =	&map_size;
	boot_map.desc_size =	&desc_size;
	boot_map.desc_ver =	NULL;
	boot_map.key_ptr =	NULL;
	boot_map.buff_size =	&buff_size;

	status = efi_get_memory_map(sys_table_arg, &boot_map);
	if (status != EFI_SUCCESS)
		goto fail;

	/*
	 * Enforce minimum alignment that EFI or Linux requires when
	 * requesting a specific address.  We are doing page-based (or
	 * larger) allocations, and both the address and size must meet
	 * alignment constraints.
	 */
	if (align < EFI_ALLOC_ALIGN)
		align = EFI_ALLOC_ALIGN;

	size = round_up(size, EFI_ALLOC_ALIGN);
	nr_pages = size / EFI_PAGE_SIZE;
again:
	for (i = 0; i < map_size / desc_size; i++) {
		efi_memory_desc_t *desc;
		unsigned long m = (unsigned long)map;
		u64 start, end;

		desc = efi_early_memdesc_ptr(m, desc_size, i);
		if (desc->type != EFI_CONVENTIONAL_MEMORY)
			continue;

		if (desc->num_pages < nr_pages)
			continue;

		start = desc->phys_addr;
		end = start + desc->num_pages * EFI_PAGE_SIZE;

		if (end > max)
			end = max;

		if ((start + size) > end)
			continue;

		if (round_down(end - size, align) < start)
			continue;

		start = round_down(end - size, align);

		/*
		 * Don't allocate at 0x0. It will confuse code that
		 * checks pointers against NULL.
		 */
		if (start == 0x0)
			continue;

		if (start > max_addr)
			max_addr = start;
	}

	if (!max_addr)
		status = EFI_NOT_FOUND;
	else {
		status = efi_call_early(allocate_pages,
					EFI_ALLOCATE_ADDRESS, EFI_LOADER_DATA,
					nr_pages, &max_addr);
		if (status != EFI_SUCCESS) {
			max = max_addr;
			max_addr = 0;
			goto again;
		}

		*addr = max_addr;
	}

	efi_call_early(free_pool, map);
fail:
	return status;
}