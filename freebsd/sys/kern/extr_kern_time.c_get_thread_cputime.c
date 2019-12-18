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
typedef  scalar_t__ uint64_t ;
struct timespec {int dummy; } ;
struct thread {scalar_t__ td_runtime; } ;
struct TYPE_2__ {scalar_t__ td_runtime; } ;

/* Variables and functions */
 scalar_t__ PCPU_GET (scalar_t__) ; 
 scalar_t__ cpu_ticks () ; 
 int /*<<< orphan*/  cputick2timespec (scalar_t__,struct timespec*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static void
get_thread_cputime(struct thread *targettd, struct timespec *ats)
{
	uint64_t runtime, curtime, switchtime;

	if (targettd == NULL) { /* current thread */
		critical_enter();
		switchtime = PCPU_GET(switchtime);
		curtime = cpu_ticks();
		runtime = curthread->td_runtime;
		critical_exit();
		runtime += curtime - switchtime;
	} else {
		thread_lock(targettd);
		runtime = targettd->td_runtime;
		thread_unlock(targettd);
	}
	cputick2timespec(runtime, ats);
}