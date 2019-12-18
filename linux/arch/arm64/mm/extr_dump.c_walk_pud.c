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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_page (struct pg_state*,unsigned long,int,int /*<<< orphan*/ ) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pud_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_sect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pmd (struct pg_state*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static void walk_pud(struct pg_state *st, pgd_t *pgdp, unsigned long start,
		     unsigned long end)
{
	unsigned long next, addr = start;
	pud_t *pudp = pud_offset(pgdp, start);

	do {
		pud_t pud = READ_ONCE(*pudp);
		next = pud_addr_end(addr, end);

		if (pud_none(pud) || pud_sect(pud)) {
			note_page(st, addr, 2, pud_val(pud));
		} else {
			BUG_ON(pud_bad(pud));
			walk_pmd(st, pudp, addr, next);
		}
	} while (pudp++, addr = next, addr != end);
}