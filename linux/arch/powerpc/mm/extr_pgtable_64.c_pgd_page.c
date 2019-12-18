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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int /*<<< orphan*/  pgd_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_is_leaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_page_vaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_pte (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

struct page *pgd_page(pgd_t pgd)
{
	if (pgd_is_leaf(pgd)) {
		VM_WARN_ON(!pgd_huge(pgd));
		return pte_page(pgd_pte(pgd));
	}
	return virt_to_page(pgd_page_vaddr(pgd));
}