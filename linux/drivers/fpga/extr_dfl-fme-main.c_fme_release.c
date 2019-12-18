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
struct inode {int dummy; } ;
struct file {struct dfl_feature_platform_data* private_data; } ;
struct dfl_feature_platform_data {struct platform_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dfl_feature_dev_use_end (struct dfl_feature_platform_data*) ; 

__attribute__((used)) static int fme_release(struct inode *inode, struct file *filp)
{
	struct dfl_feature_platform_data *pdata = filp->private_data;
	struct platform_device *pdev = pdata->dev;

	dev_dbg(&pdev->dev, "Device File Release\n");
	dfl_feature_dev_use_end(pdata);

	return 0;
}