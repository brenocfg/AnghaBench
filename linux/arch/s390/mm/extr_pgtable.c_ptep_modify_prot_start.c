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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgste_t ;

/* Variables and functions */
 int _PGSTE_GPS_NODAT ; 
 scalar_t__ mm_has_pgste (struct mm_struct*) ; 
 int /*<<< orphan*/  pgste_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgste_update_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_struct*) ; 
 int pgste_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  ptep_flush_lazy (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptep_xchg_start (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 

pte_t ptep_modify_prot_start(struct vm_area_struct *vma, unsigned long addr,
			     pte_t *ptep)
{
	pgste_t pgste;
	pte_t old;
	int nodat;
	struct mm_struct *mm = vma->vm_mm;

	preempt_disable();
	pgste = ptep_xchg_start(mm, addr, ptep);
	nodat = !!(pgste_val(pgste) & _PGSTE_GPS_NODAT);
	old = ptep_flush_lazy(mm, addr, ptep, nodat);
	if (mm_has_pgste(mm)) {
		pgste = pgste_update_all(old, pgste, mm);
		pgste_set(ptep, pgste);
	}
	return old;
}