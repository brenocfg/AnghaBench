#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct kdb_dbbe {int (* dbbe_trap ) (int,int) ;char* dbbe_name; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_3__ {int td_stopsched; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_AND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_NAND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  cngrab () ; 
 int /*<<< orphan*/  cnungrab () ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  kdb_cpu_trap (int,int) ; 
 struct kdb_dbbe* kdb_dbbe ; 
 struct trapframe* kdb_frame ; 
 int /*<<< orphan*/  kdb_pcb ; 
 int /*<<< orphan*/  kdb_thr_select (TYPE_1__*) ; 
 int /*<<< orphan*/  makectx (struct trapframe*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  restart_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_cpus_hard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stopped_cpus ; 
 int stub1 (int,int) ; 

int
kdb_trap(int type, int code, struct trapframe *tf)
{
#ifdef SMP
	cpuset_t other_cpus;
#endif
	struct kdb_dbbe *be;
	register_t intr;
	int handled;
	int did_stop_cpus;

	be = kdb_dbbe;
	if (be == NULL || be->dbbe_trap == NULL)
		return (0);

	/* We reenter the debugger through kdb_reenter(). */
	if (kdb_active)
		return (0);

	intr = intr_disable();

	if (!SCHEDULER_STOPPED()) {
#ifdef SMP
		other_cpus = all_cpus;
		CPU_NAND(&other_cpus, &stopped_cpus);
		CPU_CLR(PCPU_GET(cpuid), &other_cpus);
		stop_cpus_hard(other_cpus);
#endif
		curthread->td_stopsched = 1;
		did_stop_cpus = 1;
	} else
		did_stop_cpus = 0;

	kdb_active++;

	kdb_frame = tf;

	/* Let MD code do its thing first... */
	kdb_cpu_trap(type, code);

	makectx(tf, &kdb_pcb);
	kdb_thr_select(curthread);

	cngrab();

	for (;;) {
		handled = be->dbbe_trap(type, code);
		if (be == kdb_dbbe)
			break;
		be = kdb_dbbe;
		if (be == NULL || be->dbbe_trap == NULL)
			break;
		printf("Switching to %s back-end\n", be->dbbe_name);
	}

	cnungrab();

	kdb_active--;

	if (did_stop_cpus) {
		curthread->td_stopsched = 0;
#ifdef SMP
		CPU_AND(&other_cpus, &stopped_cpus);
		restart_cpus(other_cpus);
#endif
	}

	intr_restore(intr);

	return (handled);
}