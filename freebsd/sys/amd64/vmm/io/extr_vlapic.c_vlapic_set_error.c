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
typedef  int /*<<< orphan*/  uint32_t ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; int /*<<< orphan*/  esr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVT_ERROR ; 
 int /*<<< orphan*/  VLAPIC_INTR_ERROR ; 
 scalar_t__ vlapic_fire_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vlapic_set_error(struct vlapic *vlapic, uint32_t mask, bool lvt_error)
{

	vlapic->esr_pending |= mask;

	/*
	 * Avoid infinite recursion if the error LVT itself is configured with
	 * an illegal vector.
	 */
	if (lvt_error)
		return;

	if (vlapic_fire_lvt(vlapic, APIC_LVT_ERROR)) {
		vmm_stat_incr(vlapic->vm, vlapic->vcpuid, VLAPIC_INTR_ERROR, 1);
	}
}