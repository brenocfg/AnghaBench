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
struct nicvf {int num_vec; TYPE_1__* msix_entries; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct resource* irq_res; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nicvf_disable_msix (struct nicvf*) ; 
 int /*<<< orphan*/  rman_get_rid (struct resource*) ; 

__attribute__((used)) static void
nicvf_release_all_interrupts(struct nicvf *nic)
{
	struct resource *res;
	int irq;
	int err;

	/* Free registered interrupts */
	for (irq = 0; irq < nic->num_vec; irq++) {
		res = nic->msix_entries[irq].irq_res;
		if (res == NULL)
			continue;
		/* Teardown interrupt first */
		if (nic->msix_entries[irq].handle != NULL) {
			err = bus_teardown_intr(nic->dev,
			    nic->msix_entries[irq].irq_res,
			    nic->msix_entries[irq].handle);
			KASSERT(err == 0,
			    ("ERROR: Unable to teardown interrupt %d", irq));
			nic->msix_entries[irq].handle = NULL;
		}

		bus_release_resource(nic->dev, SYS_RES_IRQ,
			    rman_get_rid(res), nic->msix_entries[irq].irq_res);
		nic->msix_entries[irq].irq_res = NULL;
	}
	/* Disable MSI-X */
	nicvf_disable_msix(nic);
}