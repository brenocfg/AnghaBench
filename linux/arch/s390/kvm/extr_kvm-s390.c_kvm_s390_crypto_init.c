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
struct TYPE_5__ {int aes_kw; int dea_kw; TYPE_2__* crycb; } ;
struct TYPE_8__ {TYPE_1__ crypto; TYPE_3__* sie_page2; } ;
struct kvm {TYPE_4__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/  dea_wrapping_key_mask; int /*<<< orphan*/  aes_wrapping_key_mask; } ;
struct TYPE_7__ {TYPE_2__ crycb; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_s390_set_crycb_format (struct kvm*) ; 
 int /*<<< orphan*/  test_kvm_facility (struct kvm*,int) ; 

__attribute__((used)) static void kvm_s390_crypto_init(struct kvm *kvm)
{
	kvm->arch.crypto.crycb = &kvm->arch.sie_page2->crycb;
	kvm_s390_set_crycb_format(kvm);

	if (!test_kvm_facility(kvm, 76))
		return;

	/* Enable AES/DEA protected key functions by default */
	kvm->arch.crypto.aes_kw = 1;
	kvm->arch.crypto.dea_kw = 1;
	get_random_bytes(kvm->arch.crypto.crycb->aes_wrapping_key_mask,
			 sizeof(kvm->arch.crypto.crycb->aes_wrapping_key_mask));
	get_random_bytes(kvm->arch.crypto.crycb->dea_wrapping_key_mask,
			 sizeof(kvm->arch.crypto.crycb->dea_wrapping_key_mask));
}