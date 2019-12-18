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
typedef  scalar_t__ u_int ;
struct dmar_unit {struct dmar_msi_data* intrs; } ;
struct dmar_msi_data {scalar_t__ irq; int /*<<< orphan*/  (* enable_intr ) (struct dmar_unit*) ;int /*<<< orphan*/  msi_uaddr_reg; int /*<<< orphan*/  msi_addr_reg; int /*<<< orphan*/  msi_data_reg; int /*<<< orphan*/  (* disable_intr ) (struct dmar_unit*) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DMAR_INTR_TOTAL ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int ENOENT ; 
 int PCIB_MAP_MSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct dmar_unit* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dmar_unit*) ; 
 int /*<<< orphan*/  stub2 (struct dmar_unit*) ; 

__attribute__((used)) static int
dmar_remap_intr(device_t dev, device_t child, u_int irq)
{
	struct dmar_unit *unit;
	struct dmar_msi_data *dmd;
	uint64_t msi_addr;
	uint32_t msi_data;
	int i, error;

	unit = device_get_softc(dev);
	for (i = 0; i < DMAR_INTR_TOTAL; i++) {
		dmd = &unit->intrs[i];
		if (irq == dmd->irq) {
			error = PCIB_MAP_MSI(device_get_parent(
			    device_get_parent(dev)),
			    dev, irq, &msi_addr, &msi_data);
			if (error != 0)
				return (error);
			DMAR_LOCK(unit);
			(dmd->disable_intr)(unit);
			dmar_write4(unit, dmd->msi_data_reg, msi_data);
			dmar_write4(unit, dmd->msi_addr_reg, msi_addr);
			dmar_write4(unit, dmd->msi_uaddr_reg, msi_addr >> 32);
			(dmd->enable_intr)(unit);
			DMAR_UNLOCK(unit);
			return (0);
		}
	}
	return (ENOENT);
}