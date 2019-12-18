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
typedef  unsigned long u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_2__ {scalar_t__ (* query_variable_info_nonblocking ) (int /*<<< orphan*/ ,unsigned long*,unsigned long*,unsigned long*) ;} ;

/* Variables and functions */
 unsigned long EFI_MIN_RESERVE ; 
 scalar_t__ EFI_OUT_OF_RESOURCES ; 
 scalar_t__ EFI_SUCCESS ; 
 TYPE_1__ efi ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,unsigned long*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static efi_status_t
query_variable_store_nonblocking(u32 attributes, unsigned long size)
{
	efi_status_t status;
	u64 storage_size, remaining_size, max_size;

	status = efi.query_variable_info_nonblocking(attributes, &storage_size,
						     &remaining_size,
						     &max_size);
	if (status != EFI_SUCCESS)
		return status;

	if (remaining_size - size < EFI_MIN_RESERVE)
		return EFI_OUT_OF_RESOURCES;

	return EFI_SUCCESS;
}