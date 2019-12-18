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
struct thread {int dummy; } ;
typedef  struct thread proc ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int /*<<< orphan*/ ,struct thread*) ; 
 struct thread* FIRST_THREAD_IN_PROC (struct thread*) ; 
 int /*<<< orphan*/  process_ctor ; 
 int /*<<< orphan*/  thread_ctor ; 

__attribute__((used)) static int
proc_ctor(void *mem, int size, void *arg, int flags)
{
	struct proc *p;
	struct thread *td;

	p = (struct proc *)mem;
	EVENTHANDLER_DIRECT_INVOKE(process_ctor, p);
	td = FIRST_THREAD_IN_PROC(p);
	if (td != NULL) {
		/* Make sure all thread constructors are executed */
		EVENTHANDLER_DIRECT_INVOKE(thread_ctor, td);
	}
	return (0);
}