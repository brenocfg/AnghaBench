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
typedef  int /*<<< orphan*/  vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  pmap_page_set_memattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_pages_array_wb(vm_page_t *pages, int addrinarray)
{
#ifdef TTM_HAS_AGP
	int i;

	for (i = 0; i < addrinarray; i++)
		pmap_page_set_memattr(pages[i], VM_MEMATTR_WRITE_BACK);
#endif
	return 0;
}