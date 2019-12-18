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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALCHEMY_USB_EHCI0 ; 
 int alchemy_usb_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alchemy_ehci_power_on(struct platform_device *pdev)
{
	return alchemy_usb_control(ALCHEMY_USB_EHCI0, 1);
}