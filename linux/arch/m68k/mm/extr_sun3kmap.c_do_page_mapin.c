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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  print_pte_vaddr (unsigned long) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun3_put_pte (unsigned long,unsigned long) ; 

__attribute__((used)) static inline void do_page_mapin(unsigned long phys, unsigned long virt,
				 unsigned long type)
{
	unsigned long pte;
	pte_t ptep;

	ptep = pfn_pte(phys >> PAGE_SHIFT, PAGE_KERNEL);
	pte = pte_val(ptep);
	pte |= type;

	sun3_put_pte(virt, pte);

#ifdef SUN3_KMAP_DEBUG
	pr_info("mapin:");
	print_pte_vaddr(virt);
#endif

}