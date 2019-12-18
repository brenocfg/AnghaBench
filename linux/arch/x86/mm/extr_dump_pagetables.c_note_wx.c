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
struct pg_state {unsigned long current_address; unsigned long start_address; unsigned long wx_pages; } ;

/* Variables and functions */
 scalar_t__ BIOS_BEGIN ; 
 scalar_t__ BIOS_END ; 
 scalar_t__ PAGE_OFFSET ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,void*) ; 
 int _PAGE_NX ; 
 int __supported_pte_mask ; 
 scalar_t__ pcibios_enabled ; 
 int /*<<< orphan*/  pr_warn_once (char*,unsigned long) ; 

__attribute__((used)) static void note_wx(struct pg_state *st)
{
	unsigned long npages;

	npages = (st->current_address - st->start_address) / PAGE_SIZE;

#ifdef CONFIG_PCI_BIOS
	/*
	 * If PCI BIOS is enabled, the PCI BIOS area is forced to WX.
	 * Inform about it, but avoid the warning.
	 */
	if (pcibios_enabled && st->start_address >= PAGE_OFFSET + BIOS_BEGIN &&
	    st->current_address <= PAGE_OFFSET + BIOS_END) {
		pr_warn_once("x86/mm: PCI BIOS W+X mapping %lu pages\n", npages);
		return;
	}
#endif
	/* Account the WX pages */
	st->wx_pages += npages;
	WARN_ONCE(__supported_pte_mask & _PAGE_NX,
		  "x86/mm: Found insecure W+X mapping at address %pS\n",
		  (void *)st->start_address);
}