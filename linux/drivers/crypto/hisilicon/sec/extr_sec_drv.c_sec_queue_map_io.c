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
struct sec_queue {int /*<<< orphan*/  regs; int /*<<< orphan*/  queue_id; TYPE_1__* dev_info; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int sec_queue_map_io(struct sec_queue *queue)
{
	struct device *dev = queue->dev_info->dev;
	struct resource *res;

	res = platform_get_resource(to_platform_device(dev),
				    IORESOURCE_MEM,
				    2 + queue->queue_id);
	if (!res) {
		dev_err(dev, "Failed to get queue %d memory resource\n",
			queue->queue_id);
		return -ENOMEM;
	}
	queue->regs = ioremap(res->start, resource_size(res));
	if (!queue->regs)
		return -ENOMEM;

	return 0;
}