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
struct TYPE_2__ {struct TYPE_2__* rmq_prev; struct TYPE_2__* rmq_next; } ;
struct pcpu {int pc_cpuid; TYPE_1__ pc_rm_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAXCPU ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct pcpu*,size_t) ; 
 int /*<<< orphan*/  cpu_pcpu_init (struct pcpu*,int,size_t) ; 
 int /*<<< orphan*/  cpuhead ; 
 struct pcpu** cpuid_to_pcpu ; 
 int /*<<< orphan*/  pc_allcpu ; 

void
pcpu_init(struct pcpu *pcpu, int cpuid, size_t size)
{

	bzero(pcpu, size);
	KASSERT(cpuid >= 0 && cpuid < MAXCPU,
	    ("pcpu_init: invalid cpuid %d", cpuid));
	pcpu->pc_cpuid = cpuid;
	cpuid_to_pcpu[cpuid] = pcpu;
	STAILQ_INSERT_TAIL(&cpuhead, pcpu, pc_allcpu);
	cpu_pcpu_init(pcpu, cpuid, size);
	pcpu->pc_rm_queue.rmq_next = &pcpu->pc_rm_queue;
	pcpu->pc_rm_queue.rmq_prev = &pcpu->pc_rm_queue;
}