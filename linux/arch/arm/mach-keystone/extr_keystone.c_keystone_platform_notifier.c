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
struct notifier_block {int dummy; } ;
struct device {int /*<<< orphan*/  dma_pfn_offset; int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 unsigned long BUS_NOTIFY_ADD_DEVICE ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keystone_dma_pfn_offset ; 

__attribute__((used)) static int keystone_platform_notifier(struct notifier_block *nb,
				      unsigned long event, void *data)
{
	struct device *dev = data;

	if (event != BUS_NOTIFY_ADD_DEVICE)
		return NOTIFY_DONE;

	if (!dev)
		return NOTIFY_BAD;

	if (!dev->of_node) {
		dev->dma_pfn_offset = keystone_dma_pfn_offset;
		dev_err(dev, "set dma_pfn_offset%08lx\n",
			dev->dma_pfn_offset);
	}
	return NOTIFY_OK;
}