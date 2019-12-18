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
 int /*<<< orphan*/  APIC_LVT_CMCI ; 
 int /*<<< orphan*/  VLAPIC_INTR_CMC ; 
 scalar_t__ vlapic_fire_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
vlapic_fire_cmci(struct vlapic *vlapic)
{

	if (vlapic_fire_lvt(vlapic, APIC_LVT_CMCI)) {
		vmm_stat_incr(vlapic->vm, vlapic->vcpuid, VLAPIC_INTR_CMC, 1);
	}
}