#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_dev {int num_hwfns; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** sp_irq; int /*<<< orphan*/ * sp_irq_rid; int /*<<< orphan*/ ** sp_handle; struct ecore_dev cdev; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_hw_stop (struct ecore_dev*) ; 
 int /*<<< orphan*/  ecore_resc_free (struct ecore_dev*) ; 

__attribute__((used)) static int
qlnx_slowpath_stop(qlnx_host_t *ha)
{
	struct ecore_dev	*cdev;
	device_t		dev = ha->pci_dev;
	int			i;

	cdev = &ha->cdev;

	ecore_hw_stop(cdev);

 	for (i = 0; i < ha->cdev.num_hwfns; i++) {

        	if (ha->sp_handle[i])
                	(void)bus_teardown_intr(dev, ha->sp_irq[i],
				ha->sp_handle[i]);

		ha->sp_handle[i] = NULL;

        	if (ha->sp_irq[i])
			(void) bus_release_resource(dev, SYS_RES_IRQ,
				ha->sp_irq_rid[i], ha->sp_irq[i]);
		ha->sp_irq[i] = NULL;
	}

        ecore_resc_free(cdev);

        return 0;
}