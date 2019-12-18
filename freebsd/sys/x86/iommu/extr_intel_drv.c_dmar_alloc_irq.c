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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct dmar_unit {struct dmar_msi_data* intrs; } ;
struct dmar_msi_data {int irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  intr_handle; int /*<<< orphan*/  msi_uaddr_reg; int /*<<< orphan*/  msi_addr_reg; int /*<<< orphan*/  msi_data_reg; int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int PCIB_ALLOC_MSIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int PCIB_MAP_MSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  PCIB_RELEASE_MSIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmar_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dmar_alloc_irq(device_t dev, struct dmar_unit *unit, int idx)
{
	device_t pcib;
	struct dmar_msi_data *dmd;
	uint64_t msi_addr;
	uint32_t msi_data;
	int error;

	dmd = &unit->intrs[idx];
	pcib = device_get_parent(device_get_parent(dev)); /* Really not pcib */
	error = PCIB_ALLOC_MSIX(pcib, dev, &dmd->irq);
	if (error != 0) {
		device_printf(dev, "cannot allocate %s interrupt, %d\n",
		    dmd->name, error);
		goto err1;
	}
	error = bus_set_resource(dev, SYS_RES_IRQ, dmd->irq_rid,
	    dmd->irq, 1);
	if (error != 0) {
		device_printf(dev, "cannot set %s interrupt resource, %d\n",
		    dmd->name, error);
		goto err2;
	}
	dmd->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &dmd->irq_rid, RF_ACTIVE);
	if (dmd->irq_res == NULL) {
		device_printf(dev,
		    "cannot allocate resource for %s interrupt\n", dmd->name);
		error = ENXIO;
		goto err3;
	}
	error = bus_setup_intr(dev, dmd->irq_res, INTR_TYPE_MISC,
	    dmd->handler, NULL, unit, &dmd->intr_handle);
	if (error != 0) {
		device_printf(dev, "cannot setup %s interrupt, %d\n",
		    dmd->name, error);
		goto err4;
	}
	bus_describe_intr(dev, dmd->irq_res, dmd->intr_handle, "%s", dmd->name);
	error = PCIB_MAP_MSI(pcib, dev, dmd->irq, &msi_addr, &msi_data);
	if (error != 0) {
		device_printf(dev, "cannot map %s interrupt, %d\n",
		    dmd->name, error);
		goto err5;
	}
	dmar_write4(unit, dmd->msi_data_reg, msi_data);
	dmar_write4(unit, dmd->msi_addr_reg, msi_addr);
	/* Only for xAPIC mode */
	dmar_write4(unit, dmd->msi_uaddr_reg, msi_addr >> 32);
	return (0);

err5:
	bus_teardown_intr(dev, dmd->irq_res, dmd->intr_handle);
err4:
	bus_release_resource(dev, SYS_RES_IRQ, dmd->irq_rid, dmd->irq_res);
err3:
	bus_delete_resource(dev, SYS_RES_IRQ, dmd->irq_rid);
err2:
	PCIB_RELEASE_MSIX(pcib, dev, dmd->irq);
	dmd->irq = -1;
err1:
	return (error);
}