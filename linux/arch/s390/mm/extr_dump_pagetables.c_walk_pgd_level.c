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
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PGDIR_SIZE ; 
 int PTRS_PER_PGD ; 
 int /*<<< orphan*/  _PAGE_INVALID ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long max_addr ; 
 int /*<<< orphan*/  memset (struct pg_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  walk_p4d_level (struct seq_file*,struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pgd_level(struct seq_file *m)
{
	unsigned long addr = 0;
	struct pg_state st;
	pgd_t *pgd;
	int i;

	memset(&st, 0, sizeof(st));
	for (i = 0; i < PTRS_PER_PGD && addr < max_addr; i++) {
		st.current_address = addr;
		pgd = pgd_offset_k(addr);
		if (!pgd_none(*pgd))
			walk_p4d_level(m, &st, pgd, addr);
		else
			note_page(m, &st, _PAGE_INVALID, 1);
		addr += PGDIR_SIZE;
		cond_resched();
	}
	/* Flush out the last page */
	st.current_address = max_addr;
	note_page(m, &st, 0, 0);
}