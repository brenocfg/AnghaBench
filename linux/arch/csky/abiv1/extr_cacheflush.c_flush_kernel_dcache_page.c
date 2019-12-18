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
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcache_wbinv_all () ; 
 scalar_t__ mapping_mapped (struct address_space*) ; 
 struct address_space* page_mapping_file (struct page*) ; 

void flush_kernel_dcache_page(struct page *page)
{
	struct address_space *mapping;

	mapping = page_mapping_file(page);

	if (!mapping || mapping_mapped(mapping))
		dcache_wbinv_all();
}