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
typedef  int /*<<< orphan*/  va_list ;
struct thread {int td_stopsched; int /*<<< orphan*/  td_flags; } ;
typedef  int intmax_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KDB_WHY_PANIC ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int RB_AUTOBOOT ; 
 int RB_DUMP ; 
 int RB_NOSYNC ; 
 int RB_POWERCYCLE ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  TDF_INPANIC ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  cngrab () ; 
 int /*<<< orphan*/  cpuid ; 
 struct thread* curthread ; 
 scalar_t__ debugger_on_panic ; 
 int /*<<< orphan*/  kdb_active ; 
 int /*<<< orphan*/  kdb_backtrace () ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kern_reboot (int) ; 
 char const* panicstr ; 
 scalar_t__ powercycle_on_panic ; 
 scalar_t__ poweroff_on_panic ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  stop_cpus_hard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_on_panic ; 
 scalar_t__ time_second ; 
 scalar_t__ trace_all_panics ; 
 scalar_t__ trace_on_panic ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void
vpanic(const char *fmt, va_list ap)
{
#ifdef SMP
	cpuset_t other_cpus;
#endif
	struct thread *td = curthread;
	int bootopt, newpanic;
	static char buf[256];

	spinlock_enter();

#ifdef SMP
	/*
	 * stop_cpus_hard(other_cpus) should prevent multiple CPUs from
	 * concurrently entering panic.  Only the winner will proceed
	 * further.
	 */
	if (panicstr == NULL && !kdb_active) {
		other_cpus = all_cpus;
		CPU_CLR(PCPU_GET(cpuid), &other_cpus);
		stop_cpus_hard(other_cpus);
	}
#endif

	/*
	 * Ensure that the scheduler is stopped while panicking, even if panic
	 * has been entered from kdb.
	 */
	td->td_stopsched = 1;

	bootopt = RB_AUTOBOOT;
	newpanic = 0;
	if (panicstr)
		bootopt |= RB_NOSYNC;
	else {
		bootopt |= RB_DUMP;
		panicstr = fmt;
		newpanic = 1;
	}

	if (newpanic) {
		(void)vsnprintf(buf, sizeof(buf), fmt, ap);
		panicstr = buf;
		cngrab();
		printf("panic: %s\n", buf);
	} else {
		printf("panic: ");
		vprintf(fmt, ap);
		printf("\n");
	}
#ifdef SMP
	printf("cpuid = %d\n", PCPU_GET(cpuid));
#endif
	printf("time = %jd\n", (intmax_t )time_second);
#ifdef KDB
	if ((newpanic || trace_all_panics) && trace_on_panic)
		kdb_backtrace();
	if (debugger_on_panic)
		kdb_enter(KDB_WHY_PANIC, "panic");
#endif
	/*thread_lock(td); */
	td->td_flags |= TDF_INPANIC;
	/* thread_unlock(td); */
	if (!sync_on_panic)
		bootopt |= RB_NOSYNC;
	if (poweroff_on_panic)
		bootopt |= RB_POWEROFF;
	if (powercycle_on_panic)
		bootopt |= RB_POWERCYCLE;
	kern_reboot(bootopt);
}