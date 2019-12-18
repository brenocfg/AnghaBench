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
struct resource {int dummy; } ;
struct nicvf {TYPE_1__* msix_entries; int /*<<< orphan*/  dev; scalar_t__ msix_enabled; } ;
struct TYPE_2__ {struct resource* irq_res; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int NICVF_INTR_ID_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nicvf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nicvf_enable_msix (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_misc_intr_handler ; 
 int /*<<< orphan*/  rman_get_rid (struct resource*) ; 

__attribute__((used)) static int
nicvf_allocate_misc_interrupt(struct nicvf *nic)
{
	struct resource *res;
	int irq, rid;
	int ret = 0;

	/* Return if mailbox interrupt is already registered */
	if (nic->msix_enabled)
		return (0);

	/* Enable MSI-X */
	if (nicvf_enable_msix(nic) != 0)
		return (ENXIO);

	irq = NICVF_INTR_ID_MISC;
	rid = irq + 1;
	nic->msix_entries[irq].irq_res = bus_alloc_resource_any(nic->dev,
	    SYS_RES_IRQ, &rid, (RF_SHAREABLE | RF_ACTIVE));
	if (nic->msix_entries[irq].irq_res == NULL) {
		device_printf(nic->dev,
		    "Could not allocate Mbox interrupt for VF%d\n",
		    device_get_unit(nic->dev));
		return (ENXIO);
	}

	ret = bus_setup_intr(nic->dev, nic->msix_entries[irq].irq_res,
	    (INTR_MPSAFE | INTR_TYPE_MISC), NULL, nicvf_misc_intr_handler, nic,
	    &nic->msix_entries[irq].handle);
	if (ret != 0) {
		res = nic->msix_entries[irq].irq_res;
		bus_release_resource(nic->dev, SYS_RES_IRQ,
			    rman_get_rid(res), res);
		nic->msix_entries[irq].irq_res = NULL;
		return (ret);
	}

	return (0);
}