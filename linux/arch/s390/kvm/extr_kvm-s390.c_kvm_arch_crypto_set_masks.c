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
struct TYPE_8__ {int /*<<< orphan*/  adm; int /*<<< orphan*/  aqm; int /*<<< orphan*/  apm; } ;
struct TYPE_7__ {int /*<<< orphan*/  adm; int /*<<< orphan*/  aqm; int /*<<< orphan*/  apm; } ;
struct kvm_s390_crypto_cb {TYPE_4__ apcb0; TYPE_3__ apcb1; } ;
struct TYPE_5__ {int crycbd; struct kvm_s390_crypto_cb* crycb; } ;
struct TYPE_6__ {TYPE_1__ crypto; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_2__ arch; } ;

/* Variables and functions */
#define  CRYCB_FORMAT0 130 
#define  CRYCB_FORMAT1 129 
#define  CRYCB_FORMAT2 128 
 int CRYCB_FORMAT_MASK ; 
 int /*<<< orphan*/  KVM_REQ_VSIE_RESTART ; 
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,unsigned long,unsigned short,unsigned short,...) ; 
 int /*<<< orphan*/  kvm_s390_sync_request_broadcast (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_block_all (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_unblock_all (struct kvm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_arch_crypto_set_masks(struct kvm *kvm, unsigned long *apm,
			       unsigned long *aqm, unsigned long *adm)
{
	struct kvm_s390_crypto_cb *crycb = kvm->arch.crypto.crycb;

	mutex_lock(&kvm->lock);
	kvm_s390_vcpu_block_all(kvm);

	switch (kvm->arch.crypto.crycbd & CRYCB_FORMAT_MASK) {
	case CRYCB_FORMAT2: /* APCB1 use 256 bits */
		memcpy(crycb->apcb1.apm, apm, 32);
		VM_EVENT(kvm, 3, "SET CRYCB: apm %016lx %016lx %016lx %016lx",
			 apm[0], apm[1], apm[2], apm[3]);
		memcpy(crycb->apcb1.aqm, aqm, 32);
		VM_EVENT(kvm, 3, "SET CRYCB: aqm %016lx %016lx %016lx %016lx",
			 aqm[0], aqm[1], aqm[2], aqm[3]);
		memcpy(crycb->apcb1.adm, adm, 32);
		VM_EVENT(kvm, 3, "SET CRYCB: adm %016lx %016lx %016lx %016lx",
			 adm[0], adm[1], adm[2], adm[3]);
		break;
	case CRYCB_FORMAT1:
	case CRYCB_FORMAT0: /* Fall through both use APCB0 */
		memcpy(crycb->apcb0.apm, apm, 8);
		memcpy(crycb->apcb0.aqm, aqm, 2);
		memcpy(crycb->apcb0.adm, adm, 2);
		VM_EVENT(kvm, 3, "SET CRYCB: apm %016lx aqm %04x adm %04x",
			 apm[0], *((unsigned short *)aqm),
			 *((unsigned short *)adm));
		break;
	default:	/* Can not happen */
		break;
	}

	/* recreate the shadow crycb for each vcpu */
	kvm_s390_sync_request_broadcast(kvm, KVM_REQ_VSIE_RESTART);
	kvm_s390_vcpu_unblock_all(kvm);
	mutex_unlock(&kvm->lock);
}