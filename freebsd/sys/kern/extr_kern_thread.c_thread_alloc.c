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
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  cpu_thread_alloc (struct thread*) ; 
 int /*<<< orphan*/  thread_reap () ; 
 int /*<<< orphan*/  thread_zone ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vm_thread_new (struct thread*,int) ; 

struct thread *
thread_alloc(int pages)
{
	struct thread *td;

	thread_reap(); /* check if any zombies to get */

	td = (struct thread *)uma_zalloc(thread_zone, M_WAITOK);
	KASSERT(td->td_kstack == 0, ("thread_alloc got thread with kstack"));
	if (!vm_thread_new(td, pages)) {
		uma_zfree(thread_zone, td);
		return (NULL);
	}
	cpu_thread_alloc(td);
	return (td);
}