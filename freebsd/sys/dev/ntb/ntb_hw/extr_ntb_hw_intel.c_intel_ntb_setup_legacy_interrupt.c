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
struct ntb_softc {int allocated_interrupts; int /*<<< orphan*/  device; TYPE_1__* int_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tag; int /*<<< orphan*/ * res; scalar_t__ rid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ntb_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ndev_irq_isr ; 

__attribute__((used)) static int
intel_ntb_setup_legacy_interrupt(struct ntb_softc *ntb)
{
	int rc;

	ntb->int_info[0].rid = 0;
	ntb->int_info[0].res = bus_alloc_resource_any(ntb->device, SYS_RES_IRQ,
	    &ntb->int_info[0].rid, RF_SHAREABLE|RF_ACTIVE);
	if (ntb->int_info[0].res == NULL) {
		device_printf(ntb->device, "bus_alloc_resource failed\n");
		return (ENOMEM);
	}

	ntb->int_info[0].tag = NULL;
	ntb->allocated_interrupts = 1;

	rc = bus_setup_intr(ntb->device, ntb->int_info[0].res,
	    INTR_MPSAFE | INTR_TYPE_MISC, NULL, ndev_irq_isr,
	    ntb, &ntb->int_info[0].tag);
	if (rc != 0) {
		device_printf(ntb->device, "bus_setup_intr failed\n");
		return (ENXIO);
	}

	return (0);
}