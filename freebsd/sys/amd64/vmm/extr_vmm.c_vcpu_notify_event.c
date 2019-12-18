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
struct vm {struct vcpu* vcpu; } ;
struct vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_notify_event_locked (struct vcpu*,int) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 

void
vcpu_notify_event(struct vm *vm, int vcpuid, bool lapic_intr)
{
	struct vcpu *vcpu = &vm->vcpu[vcpuid];

	vcpu_lock(vcpu);
	vcpu_notify_event_locked(vcpu, lapic_intr);
	vcpu_unlock(vcpu);
}