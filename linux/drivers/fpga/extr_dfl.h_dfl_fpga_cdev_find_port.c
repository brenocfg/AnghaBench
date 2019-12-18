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
struct platform_device {int dummy; } ;
struct dfl_fpga_cdev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct platform_device* __dfl_fpga_cdev_find_port (struct dfl_fpga_cdev*,void*,int (*) (struct platform_device*,void*)) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct platform_device *
dfl_fpga_cdev_find_port(struct dfl_fpga_cdev *cdev, void *data,
			int (*match)(struct platform_device *, void *))
{
	struct platform_device *pdev;

	mutex_lock(&cdev->lock);
	pdev = __dfl_fpga_cdev_find_port(cdev, data, match);
	mutex_unlock(&cdev->lock);

	return pdev;
}