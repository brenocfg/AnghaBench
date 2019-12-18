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
struct usb_hcd {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  admhc_adm5120_remove (struct usb_hcd*,struct platform_device*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int usb_hcd_adm5120_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	admhc_adm5120_remove(hcd, pdev);

	return 0;
}