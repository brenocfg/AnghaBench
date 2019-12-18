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
struct callout_cpu {int dummy; } ;
struct callout {int c_cpu; } ;

/* Variables and functions */
 struct callout_cpu* CC_CPU (int) ; 
 int /*<<< orphan*/  CC_LOCK (struct callout_cpu*) ; 
 int /*<<< orphan*/  CC_UNLOCK (struct callout_cpu*) ; 
 int CPUBLOCK ; 
 int /*<<< orphan*/  cpu_spinwait () ; 

__attribute__((used)) static struct callout_cpu *
callout_lock(struct callout *c)
{
	struct callout_cpu *cc;
	int cpu;

	for (;;) {
		cpu = c->c_cpu;
#ifdef SMP
		if (cpu == CPUBLOCK) {
			while (c->c_cpu == CPUBLOCK)
				cpu_spinwait();
			continue;
		}
#endif
		cc = CC_CPU(cpu);
		CC_LOCK(cc);
		if (cpu == c->c_cpu)
			break;
		CC_UNLOCK(cc);
	}
	return (cc);
}