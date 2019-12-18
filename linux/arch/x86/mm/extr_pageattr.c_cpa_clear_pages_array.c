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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPA_PAGES_ARRAY ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int change_page_attr_set_clr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page**) ; 

__attribute__((used)) static inline int cpa_clear_pages_array(struct page **pages, int numpages,
					 pgprot_t mask)
{
	return change_page_attr_set_clr(NULL, numpages, __pgprot(0), mask, 0,
		CPA_PAGES_ARRAY, pages);
}