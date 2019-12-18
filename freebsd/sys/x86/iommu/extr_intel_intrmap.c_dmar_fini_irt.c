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
struct dmar_unit {int irte_cnt; int /*<<< orphan*/ * irt; int /*<<< orphan*/  irtids; scalar_t__ ir_enabled; } ;
typedef  int /*<<< orphan*/  dmar_irte_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmar_disable_ir (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_invalidate_iec_glob (struct dmar_unit*) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmem_destroy (int /*<<< orphan*/ ) ; 

void
dmar_fini_irt(struct dmar_unit *unit)
{

	unit->ir_enabled = 0;
	if (unit->irt != NULL) {
		dmar_disable_ir(unit);
		dmar_qi_invalidate_iec_glob(unit);
		vmem_destroy(unit->irtids);
		kmem_free((vm_offset_t)unit->irt, unit->irte_cnt *
		    sizeof(dmar_irte_t));
	}
}