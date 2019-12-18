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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zynqmp_pm_api_debugfs_exit () ; 

__attribute__((used)) static int zynqmp_firmware_remove(struct platform_device *pdev)
{
	mfd_remove_devices(&pdev->dev);
	zynqmp_pm_api_debugfs_exit();

	return 0;
}