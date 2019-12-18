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
struct thread {scalar_t__ td_kstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  cpu_thread_alloc (struct thread*) ; 
 int /*<<< orphan*/  vm_thread_new (struct thread*,int) ; 

int
thread_alloc_stack(struct thread *td, int pages)
{

	KASSERT(td->td_kstack == 0,
	    ("thread_alloc_stack called on a thread with kstack"));
	if (!vm_thread_new(td, pages))
		return (0);
	cpu_thread_alloc(td);
	return (1);
}