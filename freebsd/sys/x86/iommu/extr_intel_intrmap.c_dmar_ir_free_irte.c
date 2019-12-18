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
typedef  size_t u_int ;
struct dmar_unit {size_t irte_cnt; int /*<<< orphan*/  irtids; TYPE_1__* irt; scalar_t__ ir_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  irte2; int /*<<< orphan*/  irte1; } ;
typedef  TYPE_1__ dmar_irte_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dmar_pte_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_qi_invalidate_iec (struct dmar_unit*,size_t,int) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int
dmar_ir_free_irte(struct dmar_unit *unit, u_int cookie)
{
	dmar_irte_t *irte;

	KASSERT(unit != NULL && unit->ir_enabled,
	    ("unmap: cookie %d unit %p", cookie, unit));
	KASSERT(cookie < unit->irte_cnt,
	    ("bad cookie %u %u", cookie, unit->irte_cnt));
	irte = &(unit->irt[cookie]);
	dmar_pte_clear(&irte->irte1);
	dmar_pte_clear(&irte->irte2);
	DMAR_LOCK(unit);
	dmar_qi_invalidate_iec(unit, cookie, 1);
	DMAR_UNLOCK(unit);
	vmem_free(unit->irtids, cookie, 1);
	return (0);
}