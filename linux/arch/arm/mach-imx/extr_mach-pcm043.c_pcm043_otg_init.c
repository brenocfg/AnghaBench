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
struct platform_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_EHCI_INTERFACE_DIFF_UNI ; 
 int mx35_initialize_usb_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm043_otg_init(struct platform_device *pdev)
{
	return mx35_initialize_usb_hw(pdev->id, MXC_EHCI_INTERFACE_DIFF_UNI);
}