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
struct intel_device {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_wakeup_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_device_list_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct intel_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int intel_remove(struct platform_device *pdev)
{
	struct intel_device *idev = platform_get_drvdata(pdev);

	device_wakeup_disable(&pdev->dev);

	mutex_lock(&intel_device_list_lock);
	list_del(&idev->list);
	mutex_unlock(&intel_device_list_lock);

	dev_info(&pdev->dev, "unregistered.\n");

	return 0;
}