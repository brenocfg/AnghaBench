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

/* Variables and functions */
 int ZPCI_PTE_INVALID ; 
 int ZPCI_TABLE_PROTECTED ; 
 int /*<<< orphan*/  entry_clr_protected (unsigned long*) ; 
 int /*<<< orphan*/  entry_set_protected (unsigned long*) ; 
 int /*<<< orphan*/  invalidate_pt_entry (unsigned long*) ; 
 int /*<<< orphan*/  set_pt_pfaa (unsigned long*,void*) ; 
 int /*<<< orphan*/  validate_pt_entry (unsigned long*) ; 

void dma_update_cpu_trans(unsigned long *entry, void *page_addr, int flags)
{
	if (flags & ZPCI_PTE_INVALID) {
		invalidate_pt_entry(entry);
	} else {
		set_pt_pfaa(entry, page_addr);
		validate_pt_entry(entry);
	}

	if (flags & ZPCI_TABLE_PROTECTED)
		entry_set_protected(entry);
	else
		entry_clr_protected(entry);
}