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
struct pg_state {int to_dmesg; int check_wx; scalar_t__ wx_pages; void* current_address; } ;
typedef  int pgprotval_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/ * INIT_PGD ; 
 int PGD_LEVEL_MULT ; 
 int PTRS_PER_PGD ; 
 int _PAGE_RW ; 
 int _PAGE_USER ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  is_hypervisor_range (int) ; 
 void* normalize_addr (int) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int,int) ; 
 int pgd_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  walk_p4d_level (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ptdump_walk_pgd_level_core(struct seq_file *m, pgd_t *pgd,
				       bool checkwx, bool dmesg)
{
	pgd_t *start = INIT_PGD;
	pgprotval_t prot, eff;
	int i;
	struct pg_state st = {};

	if (pgd) {
		start = pgd;
		st.to_dmesg = dmesg;
	}

	st.check_wx = checkwx;
	if (checkwx)
		st.wx_pages = 0;

	for (i = 0; i < PTRS_PER_PGD; i++) {
		st.current_address = normalize_addr(i * PGD_LEVEL_MULT);
		if (!pgd_none(*start) && !is_hypervisor_range(i)) {
			prot = pgd_flags(*start);
#ifdef CONFIG_X86_PAE
			eff = _PAGE_USER | _PAGE_RW;
#else
			eff = prot;
#endif
			if (pgd_large(*start) || !pgd_present(*start)) {
				note_page(m, &st, __pgprot(prot), eff, 1);
			} else {
				walk_p4d_level(m, &st, *start, eff,
					       i * PGD_LEVEL_MULT);
			}
		} else
			note_page(m, &st, __pgprot(0), 0, 1);

		cond_resched();
		start++;
	}

	/* Flush out the last page */
	st.current_address = normalize_addr(PTRS_PER_PGD*PGD_LEVEL_MULT);
	note_page(m, &st, __pgprot(0), 0, 0);
	if (!checkwx)
		return;
	if (st.wx_pages)
		pr_info("x86/mm: Checked W+X mappings: FAILED, %lu W+X pages found.\n",
			st.wx_pages);
	else
		pr_info("x86/mm: Checked W+X mappings: passed, no W+X pages found.\n");
}