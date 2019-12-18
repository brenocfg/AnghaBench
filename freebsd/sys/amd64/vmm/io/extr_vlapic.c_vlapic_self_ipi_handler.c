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
typedef  int uint64_t ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIS_SENT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VLAPIC_CTR1 (struct vlapic*,char*,int) ; 
 int /*<<< orphan*/  lapic_intr_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmm_stat_array_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  x2apic (struct vlapic*) ; 

void
vlapic_self_ipi_handler(struct vlapic *vlapic, uint64_t val)
{
	int vec;

	KASSERT(x2apic(vlapic), ("SELF_IPI does not exist in xAPIC mode"));

	vec = val & 0xff;
	lapic_intr_edge(vlapic->vm, vlapic->vcpuid, vec);
	vmm_stat_array_incr(vlapic->vm, vlapic->vcpuid, IPIS_SENT,
	    vlapic->vcpuid, 1);
	VLAPIC_CTR1(vlapic, "vlapic self-ipi %d", vec);
}