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
struct dmar_unit {int /*<<< orphan*/ * ctx_obj; int /*<<< orphan*/ * domids; int /*<<< orphan*/ * regs; int /*<<< orphan*/  reg_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DMAR_INTR_TOTAL ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_fini_busdma (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_fini_fault_log (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_fini_irt (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_fini_qi (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_release_intr (int /*<<< orphan*/ ,struct dmar_unit*,int) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmar_release_resources(device_t dev, struct dmar_unit *unit)
{
	int i;

	dmar_fini_busdma(unit);
	dmar_fini_irt(unit);
	dmar_fini_qi(unit);
	dmar_fini_fault_log(unit);
	for (i = 0; i < DMAR_INTR_TOTAL; i++)
		dmar_release_intr(dev, unit, i);
	if (unit->regs != NULL) {
		bus_deactivate_resource(dev, SYS_RES_MEMORY, unit->reg_rid,
		    unit->regs);
		bus_release_resource(dev, SYS_RES_MEMORY, unit->reg_rid,
		    unit->regs);
		unit->regs = NULL;
	}
	if (unit->domids != NULL) {
		delete_unrhdr(unit->domids);
		unit->domids = NULL;
	}
	if (unit->ctx_obj != NULL) {
		vm_object_deallocate(unit->ctx_obj);
		unit->ctx_obj = NULL;
	}
}