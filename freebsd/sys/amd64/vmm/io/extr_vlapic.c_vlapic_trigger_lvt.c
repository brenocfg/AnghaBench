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
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
#define  APIC_LVT_CMCI 134 
#define  APIC_LVT_ERROR 133 
#define  APIC_LVT_LINT0 132 
#define  APIC_LVT_LINT1 131 
#define  APIC_LVT_PMC 130 
#define  APIC_LVT_THERMAL 129 
#define  APIC_LVT_TIMER 128 
 int EINVAL ; 
 int /*<<< orphan*/  LVTS_TRIGGERRED ; 
 int vlapic_enabled (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_fire_lvt (struct vlapic*,int) ; 
 int /*<<< orphan*/  vm_inject_extint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_inject_nmi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_array_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
vlapic_trigger_lvt(struct vlapic *vlapic, int vector)
{

	if (vlapic_enabled(vlapic) == false) {
		/*
		 * When the local APIC is global/hardware disabled,
		 * LINT[1:0] pins are configured as INTR and NMI pins,
		 * respectively.
		*/
		switch (vector) {
			case APIC_LVT_LINT0:
				vm_inject_extint(vlapic->vm, vlapic->vcpuid);
				break;
			case APIC_LVT_LINT1:
				vm_inject_nmi(vlapic->vm, vlapic->vcpuid);
				break;
			default:
				break;
		}
		return (0);
	}

	switch (vector) {
	case APIC_LVT_LINT0:
	case APIC_LVT_LINT1:
	case APIC_LVT_TIMER:
	case APIC_LVT_ERROR:
	case APIC_LVT_PMC:
	case APIC_LVT_THERMAL:
	case APIC_LVT_CMCI:
		if (vlapic_fire_lvt(vlapic, vector)) {
			vmm_stat_array_incr(vlapic->vm, vlapic->vcpuid,
			    LVTS_TRIGGERRED, vector, 1);
		}
		break;
	default:
		return (EINVAL);
	}
	return (0);
}