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
struct dmar_unit {struct dmar_msi_data* intrs; } ;
struct dmar_msi_data {int irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  intr_handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIB_RELEASE_MSIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmar_release_intr(device_t dev, struct dmar_unit *unit, int idx)
{
	struct dmar_msi_data *dmd;

	dmd = &unit->intrs[idx];
	if (dmd->irq == -1)
		return;
	bus_teardown_intr(dev, dmd->irq_res, dmd->intr_handle);
	bus_release_resource(dev, SYS_RES_IRQ, dmd->irq_rid, dmd->irq_res);
	bus_delete_resource(dev, SYS_RES_IRQ, dmd->irq_rid);
	PCIB_RELEASE_MSIX(device_get_parent(device_get_parent(dev)),
	    dev, dmd->irq);
	dmd->irq = -1;
}