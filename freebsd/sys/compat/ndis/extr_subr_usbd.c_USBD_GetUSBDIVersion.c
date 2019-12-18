#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uvi_supported_vers; int /*<<< orphan*/  uvi_usbdi_vers; } ;
typedef  TYPE_1__ usbd_version_info ;

/* Variables and functions */
 int /*<<< orphan*/  USBDI_VERSION ; 
 int /*<<< orphan*/  USB_VER_2_0 ; 

__attribute__((used)) static void
USBD_GetUSBDIVersion(usbd_version_info *ui)
{

	/* Pretend to be Windows XP. */

	ui->uvi_usbdi_vers = USBDI_VERSION;
	ui->uvi_supported_vers = USB_VER_2_0;
}