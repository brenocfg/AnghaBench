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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_ID_AA64ZFR0_EL1 ; 
 int /*<<< orphan*/  read_sanitised_ftr_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_has_sve (struct kvm_vcpu const*) ; 

__attribute__((used)) static u64 guest_id_aa64zfr0_el1(const struct kvm_vcpu *vcpu)
{
	if (!vcpu_has_sve(vcpu))
		return 0;

	return read_sanitised_ftr_reg(SYS_ID_AA64ZFR0_EL1);
}