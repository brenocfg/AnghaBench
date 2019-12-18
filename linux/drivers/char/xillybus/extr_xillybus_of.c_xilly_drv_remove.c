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
struct xilly_endpoint {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 struct xilly_endpoint* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  xillybus_endpoint_remove (struct xilly_endpoint*) ; 

__attribute__((used)) static int xilly_drv_remove(struct platform_device *op)
{
	struct device *dev = &op->dev;
	struct xilly_endpoint *endpoint = dev_get_drvdata(dev);

	xillybus_endpoint_remove(endpoint);

	return 0;
}