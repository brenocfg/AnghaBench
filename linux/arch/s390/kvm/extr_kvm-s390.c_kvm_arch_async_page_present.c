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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pfault_token; } ;
struct kvm_async_pf {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kvm_inject_pfault_token (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_s390_pfault_done (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_arch_async_page_present(struct kvm_vcpu *vcpu,
				 struct kvm_async_pf *work)
{
	trace_kvm_s390_pfault_done(vcpu, work->arch.pfault_token);
	__kvm_inject_pfault_token(vcpu, false, work->arch.pfault_token);
}