#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* InstallMultipleProtocolInterfaces ) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * DriverBindingHandle; int /*<<< orphan*/  ImageHandle; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  TYPE_1__ EFI_DRIVER_BINDING ;

/* Variables and functions */
 TYPE_4__* BS ; 
 int /*<<< orphan*/  DriverBindingProtocolGUID ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IH ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

EFI_STATUS
install_driver(EFI_DRIVER_BINDING *driver)
{
        EFI_STATUS status;

        driver->ImageHandle = IH;
        driver->DriverBindingHandle = NULL;
        status = BS->InstallMultipleProtocolInterfaces(
            &(driver->DriverBindingHandle),
            &DriverBindingProtocolGUID, driver,
            NULL);

        if (EFI_ERROR(status)) {
                printf("Failed to install driver (%ld)!\n",
                    EFI_ERROR_CODE(status));
        }

        return (status);
}