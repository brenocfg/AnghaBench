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
struct edac_device_ctl_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct edac_device_ctl_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_device_del_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (struct edac_device_ctl_info*) ; 

__attribute__((used)) static int qcom_llcc_edac_remove(struct platform_device *pdev)
{
	struct edac_device_ctl_info *edev_ctl = dev_get_drvdata(&pdev->dev);

	edac_device_del_device(edev_ctl->dev);
	edac_device_free_ctl_info(edev_ctl);

	return 0;
}