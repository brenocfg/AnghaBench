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
struct TYPE_2__ {int /*<<< orphan*/  (* FreePool ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 TYPE_1__* BS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void efi_devpath_free(EFI_DEVICE_PATH *devpath)
{

	BS->FreePool(devpath);
}