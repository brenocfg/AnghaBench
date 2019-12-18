#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {char* name; int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_6__ {scalar_t__ start; } ;
struct pci_pbm_info {int /*<<< orphan*/  name; TYPE_3__ mem_space; TYPE_2__* op; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_BUSY ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_resource (TYPE_3__*,struct resource*) ; 

__attribute__((used)) static void pci_register_iommu_region(struct pci_pbm_info *pbm)
{
	const u32 *vdma = of_get_property(pbm->op->dev.of_node, "virtual-dma",
					  NULL);

	if (vdma) {
		struct resource *rp = kzalloc(sizeof(*rp), GFP_KERNEL);

		if (!rp) {
			pr_info("%s: Cannot allocate IOMMU resource.\n",
				pbm->name);
			return;
		}
		rp->name = "IOMMU";
		rp->start = pbm->mem_space.start + (unsigned long) vdma[0];
		rp->end = rp->start + (unsigned long) vdma[1] - 1UL;
		rp->flags = IORESOURCE_BUSY;
		if (request_resource(&pbm->mem_space, rp)) {
			pr_info("%s: Unable to request IOMMU resource.\n",
				pbm->name);
			kfree(rp);
		}
	}
}