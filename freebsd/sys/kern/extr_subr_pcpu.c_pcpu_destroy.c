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
struct pcpu {size_t pc_cpuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct pcpu*,struct pcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuhead ; 
 int /*<<< orphan*/ ** cpuid_to_pcpu ; 
 scalar_t__* dpcpu_off ; 
 int /*<<< orphan*/  pc_allcpu ; 

void
pcpu_destroy(struct pcpu *pcpu)
{

	STAILQ_REMOVE(&cpuhead, pcpu, pcpu, pc_allcpu);
	cpuid_to_pcpu[pcpu->pc_cpuid] = NULL;
	dpcpu_off[pcpu->pc_cpuid] = 0;
}