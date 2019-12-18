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
 int /*<<< orphan*/  APIC_LVT_TIMER ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VLAPIC_CTR0 (struct vlapic*,char*) ; 
 int /*<<< orphan*/  VLAPIC_INTR_TIMER ; 
 int /*<<< orphan*/  VLAPIC_TIMER_LOCKED (struct vlapic*) ; 
 scalar_t__ vlapic_fire_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vlapic_fire_timer(struct vlapic *vlapic)
{

	KASSERT(VLAPIC_TIMER_LOCKED(vlapic), ("vlapic_fire_timer not locked"));

	if (vlapic_fire_lvt(vlapic, APIC_LVT_TIMER)) {
		VLAPIC_CTR0(vlapic, "vlapic timer fired");
		vmm_stat_incr(vlapic->vm, vlapic->vcpuid, VLAPIC_INTR_TIMER, 1);
	}
}