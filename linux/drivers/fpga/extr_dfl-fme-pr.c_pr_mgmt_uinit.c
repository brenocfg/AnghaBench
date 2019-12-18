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
struct dfl_feature {int dummy; } ;

/* Variables and functions */
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfl_fme_destroy_bridges (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  dfl_fme_destroy_mgr (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  dfl_fme_destroy_regions (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pr_mgmt_uinit(struct platform_device *pdev,
			  struct dfl_feature *feature)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&pdev->dev);

	mutex_lock(&pdata->lock);

	dfl_fme_destroy_regions(pdata);
	dfl_fme_destroy_bridges(pdata);
	dfl_fme_destroy_mgr(pdata);
	mutex_unlock(&pdata->lock);
}