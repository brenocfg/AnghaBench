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
struct pi_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pi_is_pir_empty (struct pi_desc*) ; 
 scalar_t__ pi_test_on (struct pi_desc*) ; 
 scalar_t__ pi_test_sn (struct pi_desc*) ; 
 struct pi_desc* vcpu_to_pi_desc (struct kvm_vcpu*) ; 

__attribute__((used)) static bool vmx_dy_apicv_has_pending_interrupt(struct kvm_vcpu *vcpu)
{
	struct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	return pi_test_on(pi_desc) ||
		(pi_test_sn(pi_desc) && !pi_is_pir_empty(pi_desc));
}