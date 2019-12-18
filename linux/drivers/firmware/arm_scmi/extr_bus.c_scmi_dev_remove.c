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
struct scmi_driver {int /*<<< orphan*/  (* remove ) (struct scmi_device*) ;} ;
struct scmi_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct scmi_device*) ; 
 struct scmi_device* to_scmi_dev (struct device*) ; 
 struct scmi_driver* to_scmi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scmi_dev_remove(struct device *dev)
{
	struct scmi_driver *scmi_drv = to_scmi_driver(dev->driver);
	struct scmi_device *scmi_dev = to_scmi_dev(dev);

	if (scmi_drv->remove)
		scmi_drv->remove(scmi_dev);

	return 0;
}