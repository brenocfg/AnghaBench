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
struct TYPE_3__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mmu {int /*<<< orphan*/  inject_page_fault; int /*<<< orphan*/  get_pdptr; int /*<<< orphan*/  get_cr3; int /*<<< orphan*/  set_cr3; } ;
struct TYPE_4__ {int /*<<< orphan*/  set_cr3; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cr3 ; 
 int /*<<< orphan*/  kvm_init_shadow_mmu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_inject_page_fault ; 
 int /*<<< orphan*/  kvm_pdptr_read ; 
 TYPE_2__* kvm_x86_ops ; 

__attribute__((used)) static void init_kvm_softmmu(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *context = vcpu->arch.mmu;

	kvm_init_shadow_mmu(vcpu);
	context->set_cr3           = kvm_x86_ops->set_cr3;
	context->get_cr3           = get_cr3;
	context->get_pdptr         = kvm_pdptr_read;
	context->inject_page_fault = kvm_inject_page_fault;
}