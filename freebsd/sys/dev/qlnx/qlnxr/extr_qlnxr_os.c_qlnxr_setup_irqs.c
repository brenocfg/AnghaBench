#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_dev {int sb_start; int num_cnq; TYPE_2__* cnq_array; TYPE_1__* ha; } ;
struct TYPE_5__ {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  num_rss; } ;
typedef  TYPE_1__ qlnx_host_t ;
struct TYPE_6__ {int irq_rid; int /*<<< orphan*/  irq_handle; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*,...) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnxr_intr ; 
 int /*<<< orphan*/  qlnxr_release_irqs (struct qlnxr_dev*) ; 

__attribute__((used)) static int
qlnxr_setup_irqs(struct qlnxr_dev *dev)
{
	int start_irq_rid;
	int i;
	qlnx_host_t *ha;

	ha = dev->ha;

	start_irq_rid = dev->sb_start + 2;

	QL_DPRINT12(ha, "enter start_irq_rid = %d num_rss = %d\n",
		start_irq_rid, dev->ha->num_rss);


        for (i = 0; i < dev->num_cnq; i++) {

		dev->cnq_array[i].irq_rid = start_irq_rid + i;
	
		dev->cnq_array[i].irq = bus_alloc_resource_any(dev->ha->pci_dev,
						SYS_RES_IRQ,
						&dev->cnq_array[i].irq_rid,
						(RF_ACTIVE | RF_SHAREABLE));

		if (dev->cnq_array[i].irq == NULL) {

			QL_DPRINT11(ha,
				"bus_alloc_resource_any failed irq_rid = %d\n",
				dev->cnq_array[i].irq_rid);

			goto qlnxr_setup_irqs_err;
		}
			
                if (bus_setup_intr(dev->ha->pci_dev,
                                dev->cnq_array[i].irq,
                                (INTR_TYPE_NET | INTR_MPSAFE),
                                NULL, qlnxr_intr, &dev->cnq_array[i],
				&dev->cnq_array[i].irq_handle)) {

			QL_DPRINT11(ha, "bus_setup_intr failed\n");
			goto qlnxr_setup_irqs_err;
                }
		QL_DPRINT12(ha, "irq_rid = %d irq = %p irq_handle = %p\n",
			dev->cnq_array[i].irq_rid, dev->cnq_array[i].irq,
			dev->cnq_array[i].irq_handle);
	}

	QL_DPRINT12(ha, "exit\n");
	return (0);

qlnxr_setup_irqs_err:
	qlnxr_release_irqs(dev);

	QL_DPRINT12(ha, "exit -1\n");
	return (-1);
}