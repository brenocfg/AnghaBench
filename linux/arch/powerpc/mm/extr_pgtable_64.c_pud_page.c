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
typedef  int /*<<< orphan*/  pud_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_is_leaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_page_vaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_pte (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

struct page *pud_page(pud_t pud)
{
	if (pud_is_leaf(pud)) {
		VM_WARN_ON(!pud_huge(pud));
		return pte_page(pud_pte(pud));
	}
	return virt_to_page(pud_page_vaddr(pud));
}