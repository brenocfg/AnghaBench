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
struct pg_state {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long TASK_SIZE_64 ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pgd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pud (struct pg_state*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static void walk_pgd(struct pg_state *st, struct mm_struct *mm,
		     unsigned long start)
{
	unsigned long end = (start < TASK_SIZE_64) ? TASK_SIZE_64 : 0;
	unsigned long next, addr = start;
	pgd_t *pgdp = pgd_offset(mm, start);

	do {
		pgd_t pgd = READ_ONCE(*pgdp);
		next = pgd_addr_end(addr, end);

		if (pgd_none(pgd)) {
			note_page(st, addr, 1, pgd_val(pgd));
		} else {
			BUG_ON(pgd_bad(pgd));
			walk_pud(st, pgdp, addr, next);
		}
	} while (pgdp++, addr = next, addr != end);
}