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
struct coreboot_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct platform_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static int framebuffer_remove(struct coreboot_device *dev)
{
	struct platform_device *pdev = dev_get_drvdata(&dev->dev);

	platform_device_unregister(pdev);

	return 0;
}