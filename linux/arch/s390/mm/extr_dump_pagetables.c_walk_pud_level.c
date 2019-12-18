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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PTRS_PER_PUD ; 
 scalar_t__ PUD_SIZE ; 
 unsigned int _PAGE_INVALID ; 
 unsigned int _REGION_ENTRY_NOEXEC ; 
 unsigned int _REGION_ENTRY_PROTECT ; 
 int __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_early_shadow_pud ; 
 unsigned long max_addr ; 
 int /*<<< orphan*/  note_kasan_early_shadow_page (struct seq_file*,struct pg_state*) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,unsigned int,int) ; 
 int p4d_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_pmd_level (struct seq_file*,struct pg_state*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void walk_pud_level(struct seq_file *m, struct pg_state *st,
			   p4d_t *p4d, unsigned long addr)
{
	unsigned int prot;
	pud_t *pud;
	int i;

#ifdef CONFIG_KASAN
	if ((p4d_val(*p4d) & PAGE_MASK) == __pa(kasan_early_shadow_pud)) {
		note_kasan_early_shadow_page(m, st);
		return;
	}
#endif

	pud = pud_offset(p4d, addr);
	for (i = 0; i < PTRS_PER_PUD && addr < max_addr; i++, pud++) {
		st->current_address = addr;
		if (!pud_none(*pud))
			if (pud_large(*pud)) {
				prot = pud_val(*pud) &
					(_REGION_ENTRY_PROTECT |
					 _REGION_ENTRY_NOEXEC);
				note_page(m, st, prot, 2);
			} else
				walk_pmd_level(m, st, pud, addr);
		else
			note_page(m, st, _PAGE_INVALID, 2);
		addr += PUD_SIZE;
	}
}