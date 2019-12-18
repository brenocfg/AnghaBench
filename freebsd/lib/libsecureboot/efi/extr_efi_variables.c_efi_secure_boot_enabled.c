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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  SetupMode ;
typedef  int /*<<< orphan*/  SecureBoot ;
typedef  scalar_t__ EFI_STATUS ;

/* Variables and functions */
 scalar_t__ EFI_NOT_FOUND ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ efi_global_getenv (char*,int*,size_t*) ; 
 int efi_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
efi_secure_boot_enabled(void)
{
	UINT8 SecureBoot;
	UINT8 SetupMode;
	size_t length;
	EFI_STATUS status;

	length = sizeof(SecureBoot);
	status = efi_global_getenv("SecureBoot", &SecureBoot, &length);
	if (status != EFI_SUCCESS) {
		if (status == EFI_NOT_FOUND)
			return (0);

		printf("Failed to read \"SecureBoot\" variable\n");
		return (-efi_status_to_errno(status));
	}

	length = sizeof(SetupMode);
	status = efi_global_getenv("SetupMode", &SetupMode, &length);
	if (status != EFI_SUCCESS)
		SetupMode = 0;

	printf("   SecureBoot: %d, SetupMode: %d\n", SecureBoot, SetupMode);

	return (SecureBoot == 1 && SetupMode == 0);
}