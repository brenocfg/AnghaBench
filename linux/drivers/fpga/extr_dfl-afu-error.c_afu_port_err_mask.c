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
struct dfl_feature_platform_data {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __afu_port_err_mask (struct device*,int) ; 
 struct dfl_feature_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afu_port_err_mask(struct device *dev, bool mask)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(dev);

	mutex_lock(&pdata->lock);
	__afu_port_err_mask(dev, mask);
	mutex_unlock(&pdata->lock);
}