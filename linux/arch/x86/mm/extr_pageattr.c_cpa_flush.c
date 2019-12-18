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
struct cpa_data {unsigned int numpages; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  X86_FEATURE_CLFLUSH ; 
 int _PAGE_PRESENT ; 
 unsigned long __cpa_addr (struct cpa_data*,unsigned int) ; 
 int /*<<< orphan*/  __cpa_flush_tlb ; 
 int /*<<< orphan*/  clflush_cache_range_opt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpa_flush_all (int) ; 
 int /*<<< orphan*/  early_boot_irqs_disabled ; 
 scalar_t__ fix_addr (unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct cpa_data*,int) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 unsigned int tlb_single_page_flush_ceiling ; 

__attribute__((used)) static void cpa_flush(struct cpa_data *data, int cache)
{
	struct cpa_data *cpa = data;
	unsigned int i;

	BUG_ON(irqs_disabled() && !early_boot_irqs_disabled);

	if (cache && !static_cpu_has(X86_FEATURE_CLFLUSH)) {
		cpa_flush_all(cache);
		return;
	}

	if (cpa->numpages <= tlb_single_page_flush_ceiling)
		on_each_cpu(__cpa_flush_tlb, cpa, 1);
	else
		flush_tlb_all();

	if (!cache)
		return;

	mb();
	for (i = 0; i < cpa->numpages; i++) {
		unsigned long addr = __cpa_addr(cpa, i);
		unsigned int level;

		pte_t *pte = lookup_address(addr, &level);

		/*
		 * Only flush present addresses:
		 */
		if (pte && (pte_val(*pte) & _PAGE_PRESENT))
			clflush_cache_range_opt((void *)fix_addr(addr), PAGE_SIZE);
	}
	mb();
}