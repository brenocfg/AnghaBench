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
struct TYPE_6__ {TYPE_2__* crycb; } ;
struct TYPE_4__ {TYPE_3__ crypto; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  apcb1; int /*<<< orphan*/  apcb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_VSIE_RESTART ; 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,char*) ; 
 int /*<<< orphan*/  kvm_s390_sync_request_broadcast (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_block_all (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_unblock_all (struct kvm*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_arch_crypto_clear_masks(struct kvm *kvm)
{
	mutex_lock(&kvm->lock);
	kvm_s390_vcpu_block_all(kvm);

	memset(&kvm->arch.crypto.crycb->apcb0, 0,
	       sizeof(kvm->arch.crypto.crycb->apcb0));
	memset(&kvm->arch.crypto.crycb->apcb1, 0,
	       sizeof(kvm->arch.crypto.crycb->apcb1));

	VM_EVENT(kvm, 3, "%s", "CLR CRYCB:");
	/* recreate the shadow crycb for each vcpu */
	kvm_s390_sync_request_broadcast(kvm, KVM_REQ_VSIE_RESTART);
	kvm_s390_vcpu_unblock_all(kvm);
	mutex_unlock(&kvm->lock);
}