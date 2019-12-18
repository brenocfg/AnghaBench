#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* md_upte; } ;
struct thread {TYPE_1__ td_md; scalar_t__ td_kstack; } ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int KSTACK_PAGES ; 
 int PAGE_SIZE ; 
 int TLBLO_SWBITS_MASK ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int* pmap_pte (int /*<<< orphan*/ ,scalar_t__) ; 

void
cpu_thread_swapin(struct thread *td)
{
	pt_entry_t *pte;
	int i;

	/*
	 * The kstack may be at a different physical address now.
	 * Cache the PTEs for the Kernel stack in the machine dependent
	 * part of the thread struct so cpu_switch() can quickly map in
	 * the pcb struct and kernel stack.
	 */
	for (i = 0; i < KSTACK_PAGES; i++) {
		pte = pmap_pte(kernel_pmap, td->td_kstack + i * PAGE_SIZE);
		td->td_md.md_upte[i] = *pte & ~TLBLO_SWBITS_MASK;
	}
}