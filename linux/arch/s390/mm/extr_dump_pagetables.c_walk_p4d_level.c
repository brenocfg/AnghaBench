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
struct seq_file {int dummy; } ;
struct pg_state {unsigned long current_address; } ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 scalar_t__ P4D_SIZE ; 
 int PAGE_MASK ; 
 int PTRS_PER_P4D ; 
 int /*<<< orphan*/  _PAGE_INVALID ; 
 int __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_early_shadow_p4d ; 
 unsigned long max_addr ; 
 int /*<<< orphan*/  note_kasan_early_shadow_page (struct seq_file*,struct pg_state*) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pud_level (struct seq_file*,struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_p4d_level(struct seq_file *m, struct pg_state *st,
			   pgd_t *pgd, unsigned long addr)
{
	p4d_t *p4d;
	int i;

#ifdef CONFIG_KASAN
	if ((pgd_val(*pgd) & PAGE_MASK) == __pa(kasan_early_shadow_p4d)) {
		note_kasan_early_shadow_page(m, st);
		return;
	}
#endif

	p4d = p4d_offset(pgd, addr);
	for (i = 0; i < PTRS_PER_P4D && addr < max_addr; i++, p4d++) {
		st->current_address = addr;
		if (!p4d_none(*p4d))
			walk_pud_level(m, st, p4d, addr);
		else
			note_page(m, st, _PAGE_INVALID, 2);
		addr += P4D_SIZE;
	}
}