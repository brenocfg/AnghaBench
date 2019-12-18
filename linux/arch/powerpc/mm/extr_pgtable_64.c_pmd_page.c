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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 scalar_t__ pmd_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_is_leaf (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_page_vaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_pte (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

struct page *pmd_page(pmd_t pmd)
{
	if (pmd_is_leaf(pmd)) {
		VM_WARN_ON(!(pmd_large(pmd) || pmd_huge(pmd)));
		return pte_page(pmd_pte(pmd));
	}
	return virt_to_page(pmd_page_vaddr(pmd));
}