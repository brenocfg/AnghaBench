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
struct vm {int dummy; } ;
struct vlapic {int dummy; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SETOF (int,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int vlapic_trigger_lvt (struct vlapic*,int) ; 
 int /*<<< orphan*/  vm_active_cpus (struct vm*) ; 
 int vm_get_maxcpus (struct vm*) ; 
 struct vlapic* vm_lapic (struct vm*,int) ; 

int
lapic_set_local_intr(struct vm *vm, int cpu, int vector)
{
	struct vlapic *vlapic;
	cpuset_t dmask;
	int error;

	if (cpu < -1 || cpu >= vm_get_maxcpus(vm))
		return (EINVAL);

	if (cpu == -1)
		dmask = vm_active_cpus(vm);
	else
		CPU_SETOF(cpu, &dmask);
	error = 0;
	while ((cpu = CPU_FFS(&dmask)) != 0) {
		cpu--;
		CPU_CLR(cpu, &dmask);
		vlapic = vm_lapic(vm, cpu);
		error = vlapic_trigger_lvt(vlapic, vector);
		if (error)
			break;
	}

	return (error);
}