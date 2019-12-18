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
struct sahara_dev {int /*<<< orphan*/  device; TYPE_1__** hw_desc; int /*<<< orphan*/ * hw_phys_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/  p2; int /*<<< orphan*/  len2; int /*<<< orphan*/  p1; int /*<<< orphan*/  len1; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int SAHARA_MAX_HW_DESC ; 
 int /*<<< orphan*/  __is_defined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void sahara_dump_descriptors(struct sahara_dev *dev)
{
	int i;

	if (!__is_defined(DEBUG))
		return;

	for (i = 0; i < SAHARA_MAX_HW_DESC; i++) {
		dev_dbg(dev->device, "Descriptor (%d) (%pad):\n",
			i, &dev->hw_phys_desc[i]);
		dev_dbg(dev->device, "\thdr = 0x%08x\n", dev->hw_desc[i]->hdr);
		dev_dbg(dev->device, "\tlen1 = %u\n", dev->hw_desc[i]->len1);
		dev_dbg(dev->device, "\tp1 = 0x%08x\n", dev->hw_desc[i]->p1);
		dev_dbg(dev->device, "\tlen2 = %u\n", dev->hw_desc[i]->len2);
		dev_dbg(dev->device, "\tp2 = 0x%08x\n", dev->hw_desc[i]->p2);
		dev_dbg(dev->device, "\tnext = 0x%08x\n",
			dev->hw_desc[i]->next);
	}
	dev_dbg(dev->device, "\n");
}