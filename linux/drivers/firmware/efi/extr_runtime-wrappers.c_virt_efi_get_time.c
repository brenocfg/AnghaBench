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
typedef  int /*<<< orphan*/  efi_time_t ;
typedef  int /*<<< orphan*/  efi_time_cap_t ;
typedef  int /*<<< orphan*/  efi_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_ABORTED ; 
 int /*<<< orphan*/  EFI_GET_TIME ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_runtime_lock ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static efi_status_t virt_efi_get_time(efi_time_t *tm, efi_time_cap_t *tc)
{
	efi_status_t status;

	if (down_interruptible(&efi_runtime_lock))
		return EFI_ABORTED;
	status = efi_queue_work(EFI_GET_TIME, tm, tc, NULL, NULL, NULL);
	up(&efi_runtime_lock);
	return status;
}