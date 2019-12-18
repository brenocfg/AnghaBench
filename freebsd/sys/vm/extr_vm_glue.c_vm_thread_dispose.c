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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct thread {int td_kstack_pages; scalar_t__ td_kstack; int /*<<< orphan*/  td_kstack_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kstack_cache ; 
 int kstack_pages ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vm_thread_stack_dispose (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
vm_thread_dispose(struct thread *td)
{
	vm_object_t ksobj;
	vm_offset_t ks;
	int pages;

	pages = td->td_kstack_pages;
	ksobj = td->td_kstack_obj;
	ks = td->td_kstack;
	td->td_kstack = 0;
	td->td_kstack_pages = 0;
	if (pages == kstack_pages)
		uma_zfree(kstack_cache, (void *)ks);
	else
		vm_thread_stack_dispose(ksobj, ks, pages);
}