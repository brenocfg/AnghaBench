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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgste_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pgste (int /*<<< orphan*/ ) ; 
 scalar_t__ mm_has_pgste (struct mm_struct*) ; 
 int /*<<< orphan*/  pgste_get_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgste_pte_notify (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pgste_t ptep_xchg_start(struct mm_struct *mm,
				      unsigned long addr, pte_t *ptep)
{
	pgste_t pgste = __pgste(0);

	if (mm_has_pgste(mm)) {
		pgste = pgste_get_lock(ptep);
		pgste = pgste_pte_notify(mm, addr, ptep, pgste);
	}
	return pgste;
}