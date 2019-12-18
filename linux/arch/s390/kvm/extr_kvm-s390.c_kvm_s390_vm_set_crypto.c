#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_device_attr {int attr; } ;
struct TYPE_5__ {int aes_kw; int dea_kw; int apie; TYPE_1__* crycb; } ;
struct TYPE_6__ {TYPE_2__ crypto; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_3__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  dea_wrapping_key_mask; int /*<<< orphan*/  aes_wrapping_key_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
#define  KVM_S390_VM_CRYPTO_DISABLE_AES_KW 133 
#define  KVM_S390_VM_CRYPTO_DISABLE_APIE 132 
#define  KVM_S390_VM_CRYPTO_DISABLE_DEA_KW 131 
#define  KVM_S390_VM_CRYPTO_ENABLE_AES_KW 130 
#define  KVM_S390_VM_CRYPTO_ENABLE_APIE 129 
#define  KVM_S390_VM_CRYPTO_ENABLE_DEA_KW 128 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,char*) ; 
 int /*<<< orphan*/  ap_instructions_available () ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_crypto_reset_all (struct kvm*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_kvm_facility (struct kvm*,int) ; 

__attribute__((used)) static int kvm_s390_vm_set_crypto(struct kvm *kvm, struct kvm_device_attr *attr)
{
	mutex_lock(&kvm->lock);
	switch (attr->attr) {
	case KVM_S390_VM_CRYPTO_ENABLE_AES_KW:
		if (!test_kvm_facility(kvm, 76)) {
			mutex_unlock(&kvm->lock);
			return -EINVAL;
		}
		get_random_bytes(
			kvm->arch.crypto.crycb->aes_wrapping_key_mask,
			sizeof(kvm->arch.crypto.crycb->aes_wrapping_key_mask));
		kvm->arch.crypto.aes_kw = 1;
		VM_EVENT(kvm, 3, "%s", "ENABLE: AES keywrapping support");
		break;
	case KVM_S390_VM_CRYPTO_ENABLE_DEA_KW:
		if (!test_kvm_facility(kvm, 76)) {
			mutex_unlock(&kvm->lock);
			return -EINVAL;
		}
		get_random_bytes(
			kvm->arch.crypto.crycb->dea_wrapping_key_mask,
			sizeof(kvm->arch.crypto.crycb->dea_wrapping_key_mask));
		kvm->arch.crypto.dea_kw = 1;
		VM_EVENT(kvm, 3, "%s", "ENABLE: DEA keywrapping support");
		break;
	case KVM_S390_VM_CRYPTO_DISABLE_AES_KW:
		if (!test_kvm_facility(kvm, 76)) {
			mutex_unlock(&kvm->lock);
			return -EINVAL;
		}
		kvm->arch.crypto.aes_kw = 0;
		memset(kvm->arch.crypto.crycb->aes_wrapping_key_mask, 0,
			sizeof(kvm->arch.crypto.crycb->aes_wrapping_key_mask));
		VM_EVENT(kvm, 3, "%s", "DISABLE: AES keywrapping support");
		break;
	case KVM_S390_VM_CRYPTO_DISABLE_DEA_KW:
		if (!test_kvm_facility(kvm, 76)) {
			mutex_unlock(&kvm->lock);
			return -EINVAL;
		}
		kvm->arch.crypto.dea_kw = 0;
		memset(kvm->arch.crypto.crycb->dea_wrapping_key_mask, 0,
			sizeof(kvm->arch.crypto.crycb->dea_wrapping_key_mask));
		VM_EVENT(kvm, 3, "%s", "DISABLE: DEA keywrapping support");
		break;
	case KVM_S390_VM_CRYPTO_ENABLE_APIE:
		if (!ap_instructions_available()) {
			mutex_unlock(&kvm->lock);
			return -EOPNOTSUPP;
		}
		kvm->arch.crypto.apie = 1;
		break;
	case KVM_S390_VM_CRYPTO_DISABLE_APIE:
		if (!ap_instructions_available()) {
			mutex_unlock(&kvm->lock);
			return -EOPNOTSUPP;
		}
		kvm->arch.crypto.apie = 0;
		break;
	default:
		mutex_unlock(&kvm->lock);
		return -ENXIO;
	}

	kvm_s390_vcpu_crypto_reset_all(kvm);
	mutex_unlock(&kvm->lock);
	return 0;
}