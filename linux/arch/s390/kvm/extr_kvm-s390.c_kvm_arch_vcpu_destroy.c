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
struct TYPE_4__ {scalar_t__ sie_block; int /*<<< orphan*/  gmap; } ;
struct kvm_vcpu {TYPE_1__ arch; TYPE_3__* kvm; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_5__ {scalar_t__ use_cmma; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,char*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gmap_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_clear_async_pf_completion_queue (struct kvm_vcpu*) ; 
 scalar_t__ kvm_is_ucontrol (TYPE_3__*) ; 
 int /*<<< orphan*/  kvm_s390_clear_local_irqs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_unsetup_cmma (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  sca_del_vcpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_s390_destroy_vcpu (int /*<<< orphan*/ ) ; 

void kvm_arch_vcpu_destroy(struct kvm_vcpu *vcpu)
{
	VCPU_EVENT(vcpu, 3, "%s", "free cpu");
	trace_kvm_s390_destroy_vcpu(vcpu->vcpu_id);
	kvm_s390_clear_local_irqs(vcpu);
	kvm_clear_async_pf_completion_queue(vcpu);
	if (!kvm_is_ucontrol(vcpu->kvm))
		sca_del_vcpu(vcpu);

	if (kvm_is_ucontrol(vcpu->kvm))
		gmap_remove(vcpu->arch.gmap);

	if (vcpu->kvm->arch.use_cmma)
		kvm_s390_vcpu_unsetup_cmma(vcpu);
	free_page((unsigned long)(vcpu->arch.sie_block));

	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(kvm_vcpu_cache, vcpu);
}