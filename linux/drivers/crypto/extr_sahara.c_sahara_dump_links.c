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
struct sahara_dev {int /*<<< orphan*/  device; TYPE_1__** hw_link; int /*<<< orphan*/ * hw_phys_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/  p; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int SAHARA_MAX_HW_LINK ; 
 int /*<<< orphan*/  __is_defined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void sahara_dump_links(struct sahara_dev *dev)
{
	int i;

	if (!__is_defined(DEBUG))
		return;

	for (i = 0; i < SAHARA_MAX_HW_LINK; i++) {
		dev_dbg(dev->device, "Link (%d) (%pad):\n",
			i, &dev->hw_phys_link[i]);
		dev_dbg(dev->device, "\tlen = %u\n", dev->hw_link[i]->len);
		dev_dbg(dev->device, "\tp = 0x%08x\n", dev->hw_link[i]->p);
		dev_dbg(dev->device, "\tnext = 0x%08x\n",
			dev->hw_link[i]->next);
	}
	dev_dbg(dev->device, "\n");
}