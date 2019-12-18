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
struct qcom_usb_extcon_info {int /*<<< orphan*/  wq_detcable; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct qcom_usb_extcon_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int qcom_usb_extcon_remove(struct platform_device *pdev)
{
	struct qcom_usb_extcon_info *info = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&info->wq_detcable);

	return 0;
}