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
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __afu_port_disable (struct platform_device*) ; 
 int /*<<< orphan*/  __afu_port_enable (struct platform_device*) ; 
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_enable_set(struct platform_device *pdev, bool enable)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&pdev->dev);
	int ret = 0;

	mutex_lock(&pdata->lock);
	if (enable)
		__afu_port_enable(pdev);
	else
		ret = __afu_port_disable(pdev);
	mutex_unlock(&pdata->lock);

	return ret;
}