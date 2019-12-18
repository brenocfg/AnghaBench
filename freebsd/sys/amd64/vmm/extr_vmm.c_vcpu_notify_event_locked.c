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
struct vcpu {int hostcpu; scalar_t__ state; int /*<<< orphan*/  vlapic; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NOCPU ; 
 scalar_t__ VCPU_RUNNING ; 
 scalar_t__ VCPU_SLEEPING ; 
 int curcpu ; 
 int /*<<< orphan*/  ipi_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlapic_post_intr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_ipinum ; 
 int /*<<< orphan*/  wakeup_one (struct vcpu*) ; 

__attribute__((used)) static void
vcpu_notify_event_locked(struct vcpu *vcpu, bool lapic_intr)
{
	int hostcpu;

	hostcpu = vcpu->hostcpu;
	if (vcpu->state == VCPU_RUNNING) {
		KASSERT(hostcpu != NOCPU, ("vcpu running on invalid hostcpu"));
		if (hostcpu != curcpu) {
			if (lapic_intr) {
				vlapic_post_intr(vcpu->vlapic, hostcpu,
				    vmm_ipinum);
			} else {
				ipi_cpu(hostcpu, vmm_ipinum);
			}
		} else {
			/*
			 * If the 'vcpu' is running on 'curcpu' then it must
			 * be sending a notification to itself (e.g. SELF_IPI).
			 * The pending event will be picked up when the vcpu
			 * transitions back to guest context.
			 */
		}
	} else {
		KASSERT(hostcpu == NOCPU, ("vcpu state %d not consistent "
		    "with hostcpu %d", vcpu->state, hostcpu));
		if (vcpu->state == VCPU_SLEEPING)
			wakeup_one(vcpu);
	}
}