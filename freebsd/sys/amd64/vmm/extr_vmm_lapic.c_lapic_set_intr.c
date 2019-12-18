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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  vcpu_notify_event (struct vm*,int,int) ; 
 scalar_t__ vlapic_set_intr_ready (struct vlapic*,int,int) ; 
 int vm_get_maxcpus (struct vm*) ; 
 struct vlapic* vm_lapic (struct vm*,int) ; 

int
lapic_set_intr(struct vm *vm, int cpu, int vector, bool level)
{
	struct vlapic *vlapic;

	if (cpu < 0 || cpu >= vm_get_maxcpus(vm))
		return (EINVAL);

	/*
	 * According to section "Maskable Hardware Interrupts" in Intel SDM
	 * vectors 16 through 255 can be delivered through the local APIC.
	 */
	if (vector < 16 || vector > 255)
		return (EINVAL);

	vlapic = vm_lapic(vm, cpu);
	if (vlapic_set_intr_ready(vlapic, vector, level))
		vcpu_notify_event(vm, cpu, true);
	return (0);
}