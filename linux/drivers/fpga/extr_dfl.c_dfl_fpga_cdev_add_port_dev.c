#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dfl_fpga_cdev {int /*<<< orphan*/  lock; int /*<<< orphan*/  port_dev_list; } ;
struct dfl_feature_platform_data {TYPE_1__* dev; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dfl_fpga_cdev_add_port_dev(struct dfl_fpga_cdev *cdev,
				       struct platform_device *port)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&port->dev);

	mutex_lock(&cdev->lock);
	list_add(&pdata->node, &cdev->port_dev_list);
	get_device(&pdata->dev->dev);
	mutex_unlock(&cdev->lock);
}