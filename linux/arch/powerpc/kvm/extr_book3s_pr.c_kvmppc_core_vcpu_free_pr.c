#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_vcpu_book3s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  shadow_vcpu; scalar_t__ shared; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vfree (struct kvmppc_vcpu_book3s*) ; 

__attribute__((used)) static void kvmppc_core_vcpu_free_pr(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);

	free_page((unsigned long)vcpu->arch.shared & PAGE_MASK);
	kvm_vcpu_uninit(vcpu);
#ifdef CONFIG_KVM_BOOK3S_32_HANDLER
	kfree(vcpu->arch.shadow_vcpu);
#endif
	vfree(vcpu_book3s);
	kmem_cache_free(kvm_vcpu_cache, vcpu);
}