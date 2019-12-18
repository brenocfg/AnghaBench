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
struct screen_info {int dummy; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_RUNTIME_SERVICES_DATA ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,struct screen_info*,...) ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  install_configuration_table ; 
 int /*<<< orphan*/  screen_info_guid ; 

struct screen_info *alloc_screen_info(efi_system_table_t *sys_table_arg)
{
	struct screen_info *si;
	efi_status_t status;

	/*
	 * Unlike on arm64, where we can directly fill out the screen_info
	 * structure from the stub, we need to allocate a buffer to hold
	 * its contents while we hand over to the kernel proper from the
	 * decompressor.
	 */
	status = efi_call_early(allocate_pool, EFI_RUNTIME_SERVICES_DATA,
				sizeof(*si), (void **)&si);

	if (status != EFI_SUCCESS)
		return NULL;

	status = efi_call_early(install_configuration_table,
				&screen_info_guid, si);
	if (status == EFI_SUCCESS)
		return si;

	efi_call_early(free_pool, si);
	return NULL;
}