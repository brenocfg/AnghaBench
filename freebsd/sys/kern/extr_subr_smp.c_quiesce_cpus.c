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
typedef  scalar_t__ u_int ;
struct pcpu {TYPE_1__* pc_idlethread; } ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_2__ {scalar_t__ td_generation; } ;

/* Variables and functions */
 scalar_t__ CPU_ABSENT (int) ; 
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int EWOULDBLOCK ; 
 int MAXCPU ; 
 int /*<<< orphan*/  curthread ; 
 int mp_maxid ; 
 struct pcpu* pcpu_find (int) ; 
 int /*<<< orphan*/  sched_bind (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_unbind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 int tsleep (int (*) (int /*<<< orphan*/ ,char const*,int),int,char const*,int) ; 

int
quiesce_cpus(cpuset_t map, const char *wmesg, int prio)
{
	struct pcpu *pcpu;
	u_int gen[MAXCPU];
	int error;
	int cpu;

	error = 0;
	for (cpu = 0; cpu <= mp_maxid; cpu++) {
		if (!CPU_ISSET(cpu, &map) || CPU_ABSENT(cpu))
			continue;
		pcpu = pcpu_find(cpu);
		gen[cpu] = pcpu->pc_idlethread->td_generation;
	}
	for (cpu = 0; cpu <= mp_maxid; cpu++) {
		if (!CPU_ISSET(cpu, &map) || CPU_ABSENT(cpu))
			continue;
		pcpu = pcpu_find(cpu);
		thread_lock(curthread);
		sched_bind(curthread, cpu);
		thread_unlock(curthread);
		while (gen[cpu] == pcpu->pc_idlethread->td_generation) {
			error = tsleep(quiesce_cpus, prio, wmesg, 1);
			if (error != EWOULDBLOCK)
				goto out;
			error = 0;
		}
	}
out:
	thread_lock(curthread);
	sched_unbind(curthread);
	thread_unlock(curthread);

	return (error);
}