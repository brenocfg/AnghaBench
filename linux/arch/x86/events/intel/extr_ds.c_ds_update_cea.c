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
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cea_set_pte (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void ds_update_cea(void *cea, void *addr, size_t size, pgprot_t prot)
{
	unsigned long start = (unsigned long)cea;
	phys_addr_t pa;
	size_t msz = 0;

	pa = virt_to_phys(addr);

	preempt_disable();
	for (; msz < size; msz += PAGE_SIZE, pa += PAGE_SIZE, cea += PAGE_SIZE)
		cea_set_pte(cea, pa, prot);

	/*
	 * This is a cross-CPU update of the cpu_entry_area, we must shoot down
	 * all TLB entries for it.
	 */
	flush_tlb_kernel_range(start, start + size);
	preempt_enable();
}