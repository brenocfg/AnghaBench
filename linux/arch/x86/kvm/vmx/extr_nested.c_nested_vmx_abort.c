#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_TRIPLE_FAULT ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nested_vmx_abort(struct kvm_vcpu *vcpu, u32 indicator)
{
	/* TODO: not to reset guest simply here. */
	kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
	pr_debug_ratelimited("kvm: nested vmx abort, indicator %d\n", indicator);
}