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
struct TYPE_3__ {scalar_t__ use_esca; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  has_64bscao; int /*<<< orphan*/  has_esca; } ;

/* Variables and functions */
 unsigned int KVM_MAX_VCPUS ; 
 unsigned int KVM_S390_BSCA_CPU_SLOTS ; 
 unsigned int KVM_S390_ESCA_CPU_SLOTS ; 
 int /*<<< orphan*/  kvm_s390_use_sca_entries () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca_switch_to_extended (struct kvm*) ; 
 TYPE_2__ sclp ; 

__attribute__((used)) static int sca_can_add_vcpu(struct kvm *kvm, unsigned int id)
{
	int rc;

	if (!kvm_s390_use_sca_entries()) {
		if (id < KVM_MAX_VCPUS)
			return true;
		return false;
	}
	if (id < KVM_S390_BSCA_CPU_SLOTS)
		return true;
	if (!sclp.has_esca || !sclp.has_64bscao)
		return false;

	mutex_lock(&kvm->lock);
	rc = kvm->arch.use_esca ? 0 : sca_switch_to_extended(kvm);
	mutex_unlock(&kvm->lock);

	return rc == 0 && id < KVM_S390_ESCA_CPU_SLOTS;
}