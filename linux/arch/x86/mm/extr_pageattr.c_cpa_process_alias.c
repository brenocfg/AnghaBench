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
struct cpa_data {int pfn; unsigned long* vaddr; int flags; scalar_t__ curpage; } ;

/* Variables and functions */
 int CPA_ARRAY ; 
 int CPA_PAGES_ARRAY ; 
 unsigned long PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 unsigned long __START_KERNEL_map ; 
 int __change_page_attr_set_clr (struct cpa_data*,int /*<<< orphan*/ ) ; 
 unsigned long __cpa_addr (struct cpa_data*,scalar_t__) ; 
 scalar_t__ __cpa_pfn_in_highmap (int) ; 
 scalar_t__ __va (int) ; 
 unsigned long _brk_end ; 
 scalar_t__ _text ; 
 int max_pfn_mapped ; 
 int /*<<< orphan*/  pfn_range_is_mapped (int,int) ; 
 unsigned long phys_base ; 
 int /*<<< orphan*/  within (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int cpa_process_alias(struct cpa_data *cpa)
{
	struct cpa_data alias_cpa;
	unsigned long laddr = (unsigned long)__va(cpa->pfn << PAGE_SHIFT);
	unsigned long vaddr;
	int ret;

	if (!pfn_range_is_mapped(cpa->pfn, cpa->pfn + 1))
		return 0;

	/*
	 * No need to redo, when the primary call touched the direct
	 * mapping already:
	 */
	vaddr = __cpa_addr(cpa, cpa->curpage);
	if (!(within(vaddr, PAGE_OFFSET,
		    PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT)))) {

		alias_cpa = *cpa;
		alias_cpa.vaddr = &laddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);
		alias_cpa.curpage = 0;

		ret = __change_page_attr_set_clr(&alias_cpa, 0);
		if (ret)
			return ret;
	}

#ifdef CONFIG_X86_64
	/*
	 * If the primary call didn't touch the high mapping already
	 * and the physical address is inside the kernel map, we need
	 * to touch the high mapped kernel as well:
	 */
	if (!within(vaddr, (unsigned long)_text, _brk_end) &&
	    __cpa_pfn_in_highmap(cpa->pfn)) {
		unsigned long temp_cpa_vaddr = (cpa->pfn << PAGE_SHIFT) +
					       __START_KERNEL_map - phys_base;
		alias_cpa = *cpa;
		alias_cpa.vaddr = &temp_cpa_vaddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);
		alias_cpa.curpage = 0;

		/*
		 * The high mapping range is imprecise, so ignore the
		 * return value.
		 */
		__change_page_attr_set_clr(&alias_cpa, 0);
	}
#endif

	return 0;
}