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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int _KERNPG_TABLE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pud (int) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_pmd_page(pud_t *pud)
{
	pmd_t *pmd = (pmd_t *)get_zeroed_page(GFP_KERNEL);
	if (!pmd)
		return -1;

	set_pud(pud, __pud(__pa(pmd) | _KERNPG_TABLE));
	return 0;
}