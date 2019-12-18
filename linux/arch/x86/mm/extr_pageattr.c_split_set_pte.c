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
struct cpa_data {int /*<<< orphan*/  force_static_prot; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPA_PROTECT ; 
 unsigned long PAGE_SIZE ; 
 unsigned int PFN_DOWN (unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_protections (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void split_set_pte(struct cpa_data *cpa, pte_t *pte, unsigned long pfn,
			  pgprot_t ref_prot, unsigned long address,
			  unsigned long size)
{
	unsigned int npg = PFN_DOWN(size);
	pgprot_t prot;

	/*
	 * If should_split_large_page() discovered an inconsistent mapping,
	 * remove the invalid protection in the split mapping.
	 */
	if (!cpa->force_static_prot)
		goto set;

	/* Hand in lpsize = 0 to enforce the protection mechanism */
	prot = static_protections(ref_prot, address, pfn, npg, 0, CPA_PROTECT);

	if (pgprot_val(prot) == pgprot_val(ref_prot))
		goto set;

	/*
	 * If this is splitting a PMD, fix it up. PUD splits cannot be
	 * fixed trivially as that would require to rescan the newly
	 * installed PMD mappings after returning from split_large_page()
	 * so an eventual further split can allocate the necessary PTE
	 * pages. Warn for now and revisit it in case this actually
	 * happens.
	 */
	if (size == PAGE_SIZE)
		ref_prot = prot;
	else
		pr_warn_once("CPA: Cannot fixup static protections for PUD split\n");
set:
	set_pte(pte, pfn_pte(pfn, ref_prot));
}