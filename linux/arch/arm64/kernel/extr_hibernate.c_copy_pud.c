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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PMD_SECT_RDONLY ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pud (int) ; 
 scalar_t__ copy_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_table (int /*<<< orphan*/ ) ; 
 int pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_pud(pgd_t *dst_pgdp, pgd_t *src_pgdp, unsigned long start,
		    unsigned long end)
{
	pud_t *dst_pudp;
	pud_t *src_pudp;
	unsigned long next;
	unsigned long addr = start;

	if (pgd_none(READ_ONCE(*dst_pgdp))) {
		dst_pudp = (pud_t *)get_safe_page(GFP_ATOMIC);
		if (!dst_pudp)
			return -ENOMEM;
		pgd_populate(&init_mm, dst_pgdp, dst_pudp);
	}
	dst_pudp = pud_offset(dst_pgdp, start);

	src_pudp = pud_offset(src_pgdp, start);
	do {
		pud_t pud = READ_ONCE(*src_pudp);

		next = pud_addr_end(addr, end);
		if (pud_none(pud))
			continue;
		if (pud_table(pud)) {
			if (copy_pmd(dst_pudp, src_pudp, addr, next))
				return -ENOMEM;
		} else {
			set_pud(dst_pudp,
				__pud(pud_val(pud) & ~PMD_SECT_RDONLY));
		}
	} while (dst_pudp++, src_pudp++, addr = next, addr != end);

	return 0;
}