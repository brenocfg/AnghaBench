#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kvm_enable_cap {int cap; scalar_t__ flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  fac_list; int /*<<< orphan*/  fac_mask; } ;
struct TYPE_8__ {int use_irqchip; int user_sigp; int user_stsi; int user_instr0; int /*<<< orphan*/  use_pfmfi; int /*<<< orphan*/  use_skf; int /*<<< orphan*/  use_cmma; TYPE_1__ model; } ;
struct kvm {TYPE_4__ arch; int /*<<< orphan*/  lock; TYPE_3__* mm; int /*<<< orphan*/  created_vcpus; } ;
struct TYPE_6__ {int allow_gmap_hpage_1m; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmap_sem; TYPE_2__ context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  KVM_CAP_S390_AIS 136 
#define  KVM_CAP_S390_GS 135 
#define  KVM_CAP_S390_HPAGE_1M 134 
#define  KVM_CAP_S390_IRQCHIP 133 
#define  KVM_CAP_S390_RI 132 
#define  KVM_CAP_S390_USER_INSTR0 131 
#define  KVM_CAP_S390_USER_SIGP 130 
#define  KVM_CAP_S390_USER_STSI 129 
#define  KVM_CAP_S390_VECTOR_REGISTERS 128 
 int /*<<< orphan*/  MACHINE_HAS_VX ; 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpage ; 
 int /*<<< orphan*/  icpt_operexc_on_all_vcpus (struct kvm*) ; 
 int /*<<< orphan*/  kvm_is_ucontrol (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_kvm_facility (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_facility (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int kvm_vm_ioctl_enable_cap(struct kvm *kvm, struct kvm_enable_cap *cap)
{
	int r;

	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
	case KVM_CAP_S390_IRQCHIP:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_IRQCHIP");
		kvm->arch.use_irqchip = 1;
		r = 0;
		break;
	case KVM_CAP_S390_USER_SIGP:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_USER_SIGP");
		kvm->arch.user_sigp = 1;
		r = 0;
		break;
	case KVM_CAP_S390_VECTOR_REGISTERS:
		mutex_lock(&kvm->lock);
		if (kvm->created_vcpus) {
			r = -EBUSY;
		} else if (MACHINE_HAS_VX) {
			set_kvm_facility(kvm->arch.model.fac_mask, 129);
			set_kvm_facility(kvm->arch.model.fac_list, 129);
			if (test_facility(134)) {
				set_kvm_facility(kvm->arch.model.fac_mask, 134);
				set_kvm_facility(kvm->arch.model.fac_list, 134);
			}
			if (test_facility(135)) {
				set_kvm_facility(kvm->arch.model.fac_mask, 135);
				set_kvm_facility(kvm->arch.model.fac_list, 135);
			}
			if (test_facility(148)) {
				set_kvm_facility(kvm->arch.model.fac_mask, 148);
				set_kvm_facility(kvm->arch.model.fac_list, 148);
			}
			if (test_facility(152)) {
				set_kvm_facility(kvm->arch.model.fac_mask, 152);
				set_kvm_facility(kvm->arch.model.fac_list, 152);
			}
			r = 0;
		} else
			r = -EINVAL;
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_VECTOR_REGISTERS %s",
			 r ? "(not available)" : "(success)");
		break;
	case KVM_CAP_S390_RI:
		r = -EINVAL;
		mutex_lock(&kvm->lock);
		if (kvm->created_vcpus) {
			r = -EBUSY;
		} else if (test_facility(64)) {
			set_kvm_facility(kvm->arch.model.fac_mask, 64);
			set_kvm_facility(kvm->arch.model.fac_list, 64);
			r = 0;
		}
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_RI %s",
			 r ? "(not available)" : "(success)");
		break;
	case KVM_CAP_S390_AIS:
		mutex_lock(&kvm->lock);
		if (kvm->created_vcpus) {
			r = -EBUSY;
		} else {
			set_kvm_facility(kvm->arch.model.fac_mask, 72);
			set_kvm_facility(kvm->arch.model.fac_list, 72);
			r = 0;
		}
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: AIS %s",
			 r ? "(not available)" : "(success)");
		break;
	case KVM_CAP_S390_GS:
		r = -EINVAL;
		mutex_lock(&kvm->lock);
		if (kvm->created_vcpus) {
			r = -EBUSY;
		} else if (test_facility(133)) {
			set_kvm_facility(kvm->arch.model.fac_mask, 133);
			set_kvm_facility(kvm->arch.model.fac_list, 133);
			r = 0;
		}
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_GS %s",
			 r ? "(not available)" : "(success)");
		break;
	case KVM_CAP_S390_HPAGE_1M:
		mutex_lock(&kvm->lock);
		if (kvm->created_vcpus)
			r = -EBUSY;
		else if (!hpage || kvm->arch.use_cmma || kvm_is_ucontrol(kvm))
			r = -EINVAL;
		else {
			r = 0;
			down_write(&kvm->mm->mmap_sem);
			kvm->mm->context.allow_gmap_hpage_1m = 1;
			up_write(&kvm->mm->mmap_sem);
			/*
			 * We might have to create fake 4k page
			 * tables. To avoid that the hardware works on
			 * stale PGSTEs, we emulate these instructions.
			 */
			kvm->arch.use_skf = 0;
			kvm->arch.use_pfmfi = 0;
		}
		mutex_unlock(&kvm->lock);
		VM_EVENT(kvm, 3, "ENABLE: CAP_S390_HPAGE %s",
			 r ? "(not available)" : "(success)");
		break;
	case KVM_CAP_S390_USER_STSI:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_USER_STSI");
		kvm->arch.user_stsi = 1;
		r = 0;
		break;
	case KVM_CAP_S390_USER_INSTR0:
		VM_EVENT(kvm, 3, "%s", "ENABLE: CAP_S390_USER_INSTR0");
		kvm->arch.user_instr0 = 1;
		icpt_operexc_on_all_vcpus(kvm);
		r = 0;
		break;
	default:
		r = -EINVAL;
		break;
	}
	return r;
}