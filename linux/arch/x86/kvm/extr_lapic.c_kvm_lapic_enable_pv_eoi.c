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
typedef  scalar_t__ u64 ;
struct gfn_to_hva_cache {scalar_t__ gpa; unsigned long len; } ;
struct TYPE_3__ {scalar_t__ msr_val; struct gfn_to_hva_cache data; } ;
struct TYPE_4__ {TYPE_1__ pv_eoi; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 scalar_t__ KVM_MSR_ENABLED ; 
 int kvm_gfn_to_hva_cache_init (int /*<<< orphan*/ ,struct gfn_to_hva_cache*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  pv_eoi_enabled (struct kvm_vcpu*) ; 

int kvm_lapic_enable_pv_eoi(struct kvm_vcpu *vcpu, u64 data, unsigned long len)
{
	u64 addr = data & ~KVM_MSR_ENABLED;
	struct gfn_to_hva_cache *ghc = &vcpu->arch.pv_eoi.data;
	unsigned long new_len;

	if (!IS_ALIGNED(addr, 4))
		return 1;

	vcpu->arch.pv_eoi.msr_val = data;
	if (!pv_eoi_enabled(vcpu))
		return 0;

	if (addr == ghc->gpa && len <= ghc->len)
		new_len = ghc->len;
	else
		new_len = len;

	return kvm_gfn_to_hva_cache_init(vcpu->kvm, ghc, addr, new_len);
}