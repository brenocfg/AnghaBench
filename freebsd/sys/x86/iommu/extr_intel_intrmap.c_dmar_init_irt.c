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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct dmar_unit {int hw_ecap; int ir_enabled; int irte_cnt; int /*<<< orphan*/  irtids; int /*<<< orphan*/ * irt; int /*<<< orphan*/  irt_phys; int /*<<< orphan*/  dev; int /*<<< orphan*/  qi_enabled; } ;
typedef  int /*<<< orphan*/  dmar_irte_t ;

/* Variables and functions */
 int DMAR_ECAP_IR ; 
 scalar_t__ DMAR_IS_COHERENT (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int ENOMEM ; 
 int M_FIRSTFIT ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ bootverbose ; 
 int clp2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmar_enable_ir (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_high ; 
 int /*<<< orphan*/  dmar_load_irt_ptr (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_invalidate_iec_glob (struct dmar_unit*) ; 
 int /*<<< orphan*/  intr_reprogram () ; 
 scalar_t__ kmem_alloc_contig (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_io_irqs ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

int
dmar_init_irt(struct dmar_unit *unit)
{

	if ((unit->hw_ecap & DMAR_ECAP_IR) == 0)
		return (0);
	unit->ir_enabled = 1;
	TUNABLE_INT_FETCH("hw.dmar.ir", &unit->ir_enabled);
	if (!unit->ir_enabled)
		return (0);
	if (!unit->qi_enabled) {
		unit->ir_enabled = 0;
		if (bootverbose)
			device_printf(unit->dev,
	     "QI disabled, disabling interrupt remapping\n");
		return (0);
	}
	unit->irte_cnt = clp2(num_io_irqs);
	unit->irt = (dmar_irte_t *)(uintptr_t)kmem_alloc_contig(
	    unit->irte_cnt * sizeof(dmar_irte_t), M_ZERO | M_WAITOK, 0,
	    dmar_high, PAGE_SIZE, 0, DMAR_IS_COHERENT(unit) ?
	    VM_MEMATTR_DEFAULT : VM_MEMATTR_UNCACHEABLE);
	if (unit->irt == NULL)
		return (ENOMEM);
	unit->irt_phys = pmap_kextract((vm_offset_t)unit->irt);
	unit->irtids = vmem_create("dmarirt", 0, unit->irte_cnt, 1, 0,
	    M_FIRSTFIT | M_NOWAIT);
	DMAR_LOCK(unit);
	dmar_load_irt_ptr(unit);
	dmar_qi_invalidate_iec_glob(unit);
	DMAR_UNLOCK(unit);

	/*
	 * Initialize mappings for already configured interrupt pins.
	 * Required, because otherwise the interrupts fault without
	 * irtes.
	 */
	intr_reprogram();

	DMAR_LOCK(unit);
	dmar_enable_ir(unit);
	DMAR_UNLOCK(unit);
	return (0);
}