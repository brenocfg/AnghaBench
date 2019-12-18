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
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {int /*<<< orphan*/  efi_rts_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_RESET_SYSTEM ; 
 int /*<<< orphan*/  __efi_call_virt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 TYPE_1__ efi_rts_work ; 
 int /*<<< orphan*/  efi_runtime_lock ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  reset_system ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virt_efi_reset_system(int reset_type,
				  efi_status_t status,
				  unsigned long data_size,
				  efi_char16_t *data)
{
	if (down_interruptible(&efi_runtime_lock)) {
		pr_warn("failed to invoke the reset_system() runtime service:\n"
			"could not get exclusive access to the firmware\n");
		return;
	}
	efi_rts_work.efi_rts_id = EFI_RESET_SYSTEM;
	__efi_call_virt(reset_system, reset_type, status, data_size, data);
	up(&efi_runtime_lock);
}