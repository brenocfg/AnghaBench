#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcpu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_attach_mask; } ;
struct TYPE_5__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_2__ init_mm ; 
 int /*<<< orphan*/ * mm_cpumask (TYPE_2__*) ; 
 struct pcpu* pcpu_devices ; 
 int /*<<< orphan*/  pcpu_free_lowcore (struct pcpu*) ; 
 int /*<<< orphan*/  pcpu_stopped (struct pcpu*) ; 

void __cpu_die(unsigned int cpu)
{
	struct pcpu *pcpu;

	/* Wait until target cpu is down */
	pcpu = pcpu_devices + cpu;
	while (!pcpu_stopped(pcpu))
		cpu_relax();
	pcpu_free_lowcore(pcpu);
	cpumask_clear_cpu(cpu, mm_cpumask(&init_mm));
	cpumask_clear_cpu(cpu, &init_mm.context.cpu_attach_mask);
}