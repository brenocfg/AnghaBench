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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PMD_SECT_RDONLY ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 scalar_t__ copy_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mm ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_table (int /*<<< orphan*/ ) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_pmd(pud_t *dst_pudp, pud_t *src_pudp, unsigned long start,
		    unsigned long end)
{
	pmd_t *src_pmdp;
	pmd_t *dst_pmdp;
	unsigned long next;
	unsigned long addr = start;

	if (pud_none(READ_ONCE(*dst_pudp))) {
		dst_pmdp = (pmd_t *)get_safe_page(GFP_ATOMIC);
		if (!dst_pmdp)
			return -ENOMEM;
		pud_populate(&init_mm, dst_pudp, dst_pmdp);
	}
	dst_pmdp = pmd_offset(dst_pudp, start);

	src_pmdp = pmd_offset(src_pudp, start);
	do {
		pmd_t pmd = READ_ONCE(*src_pmdp);

		next = pmd_addr_end(addr, end);
		if (pmd_none(pmd))
			continue;
		if (pmd_table(pmd)) {
			if (copy_pte(dst_pmdp, src_pmdp, addr, next))
				return -ENOMEM;
		} else {
			set_pmd(dst_pmdp,
				__pmd(pmd_val(pmd) & ~PMD_SECT_RDONLY));
		}
	} while (dst_pmdp++, src_pmdp++, addr = next, addr != end);

	return 0;
}