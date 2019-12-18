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
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 int _efi_devpath_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool
efi_devpath_match(EFI_DEVICE_PATH *devpath1, EFI_DEVICE_PATH *devpath2)
{
	return _efi_devpath_match(devpath1, devpath2, false);
}