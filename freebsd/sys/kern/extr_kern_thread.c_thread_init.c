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
struct thread {int /*<<< orphan*/ * td_sel; scalar_t__ td_kstack; int /*<<< orphan*/ * td_rlqe; int /*<<< orphan*/  td_turnstile; int /*<<< orphan*/  td_sleepqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int (*) (void*,int,int),struct thread*) ; 
 int /*<<< orphan*/  sleepq_alloc () ; 
 int /*<<< orphan*/  turnstile_alloc () ; 
 int /*<<< orphan*/  umtx_thread_init (struct thread*) ; 

__attribute__((used)) static int
thread_init(void *mem, int size, int flags)
{
	struct thread *td;

	td = (struct thread *)mem;

	td->td_sleepqueue = sleepq_alloc();
	td->td_turnstile = turnstile_alloc();
	td->td_rlqe = NULL;
	EVENTHANDLER_DIRECT_INVOKE(thread_init, td);
	umtx_thread_init(td);
	td->td_kstack = 0;
	td->td_sel = NULL;
	return (0);
}