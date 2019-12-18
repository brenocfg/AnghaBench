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
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int secondary_ctls_high; } ;
struct TYPE_5__ {TYPE_1__ msrs; } ;
struct TYPE_6__ {TYPE_2__ nested; } ;

/* Variables and functions */
 int SECONDARY_EXEC_SHADOW_VMCS ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool nested_cpu_has_vmx_shadow_vmcs(struct kvm_vcpu *vcpu)
{
	return to_vmx(vcpu)->nested.msrs.secondary_ctls_high &
		SECONDARY_EXEC_SHADOW_VMCS;
}