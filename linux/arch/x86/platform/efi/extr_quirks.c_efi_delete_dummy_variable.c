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
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_variable_nonblocking ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_DUMMY_GUID ; 
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_NON_VOLATILE ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 TYPE_1__ efi ; 
 scalar_t__ efi_dummy_name ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void efi_delete_dummy_variable(void)
{
	efi.set_variable_nonblocking((efi_char16_t *)efi_dummy_name,
				     &EFI_DUMMY_GUID,
				     EFI_VARIABLE_NON_VOLATILE |
				     EFI_VARIABLE_BOOTSERVICE_ACCESS |
				     EFI_VARIABLE_RUNTIME_ACCESS, 0, NULL);
}