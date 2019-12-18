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
typedef  size_t uint32_t ;
struct ntb_softc {int /*<<< orphan*/  device; TYPE_1__* int_info; int /*<<< orphan*/ * msix_vec; int /*<<< orphan*/  allocated_interrupts; } ;
struct TYPE_2__ {size_t rid; int /*<<< orphan*/ * tag; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ndev_vec_isr ; 

__attribute__((used)) static int
intel_ntb_setup_msix(struct ntb_softc *ntb, uint32_t num_vectors)
{
	uint32_t i;
	int rc;

	for (i = 0; i < num_vectors; i++) {
		ntb->int_info[i].rid = i + 1;
		ntb->int_info[i].res = bus_alloc_resource_any(ntb->device,
		    SYS_RES_IRQ, &ntb->int_info[i].rid, RF_ACTIVE);
		if (ntb->int_info[i].res == NULL) {
			device_printf(ntb->device,
			    "bus_alloc_resource failed\n");
			return (ENOMEM);
		}
		ntb->int_info[i].tag = NULL;
		ntb->allocated_interrupts++;
		rc = bus_setup_intr(ntb->device, ntb->int_info[i].res,
		    INTR_MPSAFE | INTR_TYPE_MISC, NULL, ndev_vec_isr,
		    &ntb->msix_vec[i], &ntb->int_info[i].tag);
		if (rc != 0) {
			device_printf(ntb->device, "bus_setup_intr failed\n");
			return (ENXIO);
		}
	}
	return (0);
}