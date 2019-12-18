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
typedef  int u_int ;
struct dmar_unit {scalar_t__ ir_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct dmar_unit* dmar_find_ioapic (int,int /*<<< orphan*/ *) ; 
 int dmar_ir_free_irte (struct dmar_unit*,int) ; 

int
iommu_unmap_ioapic_intr(u_int ioapic_id, u_int *cookie)
{
	struct dmar_unit *unit;
	u_int idx;

	idx = *cookie;
	if (idx == -1)
		return (0);
	*cookie = -1;
	unit = dmar_find_ioapic(ioapic_id, NULL);
	KASSERT(unit != NULL && unit->ir_enabled,
	    ("unmap: cookie %d unit %p", idx, unit));
	return (dmar_ir_free_irte(unit, idx));
}