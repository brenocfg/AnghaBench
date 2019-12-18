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
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  unsigned long efi_physical_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ALLOCATE_ADDRESS ; 
 int /*<<< orphan*/  EFI_ALLOC_ALIGN ; 
 scalar_t__ EFI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 unsigned long EFI_PAGE_SIZE ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pages ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long*) ; 
 scalar_t__ efi_low_alloc_above (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 int /*<<< orphan*/  pr_efi_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 

efi_status_t efi_relocate_kernel(efi_system_table_t *sys_table_arg,
				 unsigned long *image_addr,
				 unsigned long image_size,
				 unsigned long alloc_size,
				 unsigned long preferred_addr,
				 unsigned long alignment,
				 unsigned long min_addr)
{
	unsigned long cur_image_addr;
	unsigned long new_addr = 0;
	efi_status_t status;
	unsigned long nr_pages;
	efi_physical_addr_t efi_addr = preferred_addr;

	if (!image_addr || !image_size || !alloc_size)
		return EFI_INVALID_PARAMETER;
	if (alloc_size < image_size)
		return EFI_INVALID_PARAMETER;

	cur_image_addr = *image_addr;

	/*
	 * The EFI firmware loader could have placed the kernel image
	 * anywhere in memory, but the kernel has restrictions on the
	 * max physical address it can run at.  Some architectures
	 * also have a prefered address, so first try to relocate
	 * to the preferred address.  If that fails, allocate as low
	 * as possible while respecting the required alignment.
	 */
	nr_pages = round_up(alloc_size, EFI_ALLOC_ALIGN) / EFI_PAGE_SIZE;
	status = efi_call_early(allocate_pages,
				EFI_ALLOCATE_ADDRESS, EFI_LOADER_DATA,
				nr_pages, &efi_addr);
	new_addr = efi_addr;
	/*
	 * If preferred address allocation failed allocate as low as
	 * possible.
	 */
	if (status != EFI_SUCCESS) {
		status = efi_low_alloc_above(sys_table_arg, alloc_size,
					     alignment, &new_addr, min_addr);
	}
	if (status != EFI_SUCCESS) {
		pr_efi_err(sys_table_arg, "Failed to allocate usable memory for kernel.\n");
		return status;
	}

	/*
	 * We know source/dest won't overlap since both memory ranges
	 * have been allocated by UEFI, so we can safely use memcpy.
	 */
	memcpy((void *)new_addr, (void *)cur_image_addr, image_size);

	/* Return the new address of the relocated image. */
	*image_addr = new_addr;

	return status;
}