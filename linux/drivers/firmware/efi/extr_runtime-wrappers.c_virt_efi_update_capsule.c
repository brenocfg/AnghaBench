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
typedef  int /*<<< orphan*/  efi_status_t ;
typedef  int /*<<< orphan*/  efi_capsule_header_t ;
struct TYPE_2__ {scalar_t__ runtime_version; } ;

/* Variables and functions */
 scalar_t__ EFI_2_00_SYSTEM_TABLE_REVISION ; 
 int /*<<< orphan*/  EFI_ABORTED ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 int /*<<< orphan*/  EFI_UPDATE_CAPSULE ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 TYPE_1__ efi ; 
 int /*<<< orphan*/  efi_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ **,unsigned long*,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_runtime_lock ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static efi_status_t virt_efi_update_capsule(efi_capsule_header_t **capsules,
					    unsigned long count,
					    unsigned long sg_list)
{
	efi_status_t status;

	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	if (down_interruptible(&efi_runtime_lock))
		return EFI_ABORTED;
	status = efi_queue_work(EFI_UPDATE_CAPSULE, capsules, &count, &sg_list,
				NULL, NULL);
	up(&efi_runtime_lock);
	return status;
}