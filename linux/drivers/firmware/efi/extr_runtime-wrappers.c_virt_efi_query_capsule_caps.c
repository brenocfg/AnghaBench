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
typedef  int /*<<< orphan*/  efi_status_t ;
typedef  int /*<<< orphan*/  efi_capsule_header_t ;
struct TYPE_2__ {scalar_t__ runtime_version; } ;

/* Variables and functions */
 scalar_t__ EFI_2_00_SYSTEM_TABLE_REVISION ; 
 int /*<<< orphan*/  EFI_ABORTED ; 
 int /*<<< orphan*/  EFI_QUERY_CAPSULE_CAPS ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 TYPE_1__ efi ; 
 int /*<<< orphan*/  efi_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned long*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_runtime_lock ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static efi_status_t virt_efi_query_capsule_caps(efi_capsule_header_t **capsules,
						unsigned long count,
						u64 *max_size,
						int *reset_type)
{
	efi_status_t status;

	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	if (down_interruptible(&efi_runtime_lock))
		return EFI_ABORTED;
	status = efi_queue_work(EFI_QUERY_CAPSULE_CAPS, capsules, &count,
				max_size, reset_type, NULL);
	up(&efi_runtime_lock);
	return status;
}