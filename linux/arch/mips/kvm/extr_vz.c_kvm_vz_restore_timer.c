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
typedef  int /*<<< orphan*/  u32 ;
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  _kvm_vz_restore_stimer (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_sw_gc0_cause (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_read_sw_gc0_compare (struct mips_coproc*) ; 
 int /*<<< orphan*/  write_gc0_compare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vz_restore_timer(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	u32 cause, compare;

	compare = kvm_read_sw_gc0_compare(cop0);
	cause = kvm_read_sw_gc0_cause(cop0);

	write_gc0_compare(compare);
	_kvm_vz_restore_stimer(vcpu, compare, cause);
}