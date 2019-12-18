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
struct thread {int /*<<< orphan*/  td_sleepqueue; int /*<<< orphan*/  td_turnstile; int /*<<< orphan*/  td_rlqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (void (*) (void*,int),struct thread*) ; 
 int /*<<< orphan*/  rlqentry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seltdfini (struct thread*) ; 
 int /*<<< orphan*/  sleepq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtx_thread_fini (struct thread*) ; 

__attribute__((used)) static void
thread_fini(void *mem, int size)
{
	struct thread *td;

	td = (struct thread *)mem;
	EVENTHANDLER_DIRECT_INVOKE(thread_fini, td);
	rlqentry_free(td->td_rlqe);
	turnstile_free(td->td_turnstile);
	sleepq_free(td->td_sleepqueue);
	umtx_thread_fini(td);
	seltdfini(td);
}