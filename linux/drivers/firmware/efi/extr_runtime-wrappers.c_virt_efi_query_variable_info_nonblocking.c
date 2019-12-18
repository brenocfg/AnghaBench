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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  efi_status_t ;
struct TYPE_2__ {scalar_t__ runtime_version; } ;

/* Variables and functions */
 scalar_t__ EFI_2_00_SYSTEM_TABLE_REVISION ; 
 int /*<<< orphan*/  EFI_NOT_READY ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 TYPE_1__ efi ; 
 int /*<<< orphan*/  efi_call_virt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_runtime_lock ; 
 int /*<<< orphan*/  query_variable_info ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static efi_status_t
virt_efi_query_variable_info_nonblocking(u32 attr,
					 u64 *storage_space,
					 u64 *remaining_space,
					 u64 *max_variable_size)
{
	efi_status_t status;

	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	if (down_trylock(&efi_runtime_lock))
		return EFI_NOT_READY;

	status = efi_call_virt(query_variable_info, attr, storage_space,
			       remaining_space, max_variable_size);
	up(&efi_runtime_lock);
	return status;
}