#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ipte_control {scalar_t__ val; int /*<<< orphan*/  kh; scalar_t__ k; } ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipte_wq; int /*<<< orphan*/  sca_lock; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 union ipte_control READ_ONCE (union ipte_control) ; 
 scalar_t__ cmpxchg (scalar_t__*,scalar_t__,scalar_t__) ; 
 union ipte_control* kvm_s390_get_ipte_control (TYPE_2__*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipte_unlock_siif(struct kvm_vcpu *vcpu)
{
	union ipte_control old, new, *ic;

	read_lock(&vcpu->kvm->arch.sca_lock);
	ic = kvm_s390_get_ipte_control(vcpu->kvm);
	do {
		old = READ_ONCE(*ic);
		new = old;
		new.kh--;
		if (!new.kh)
			new.k = 0;
	} while (cmpxchg(&ic->val, old.val, new.val) != old.val);
	read_unlock(&vcpu->kvm->arch.sca_lock);
	if (!new.kh)
		wake_up(&vcpu->kvm->arch.ipte_wq);
}