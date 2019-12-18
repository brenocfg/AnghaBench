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
struct virtio_uml_platform_data {int /*<<< orphan*/  socket_path; } ;
struct TYPE_2__ {struct virtio_uml_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int vu_unregister_cmdline_device(struct device *dev, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct virtio_uml_platform_data *pdata = pdev->dev.platform_data;

	kfree(pdata->socket_path);
	platform_device_unregister(pdev);
	return 0;
}