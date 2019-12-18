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
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ kvm_mips_count_disabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_read_count_running (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_count (struct mips_coproc*) ; 

u32 kvm_mips_read_count(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;

	/* If count disabled just read static copy of count */
	if (kvm_mips_count_disabled(vcpu))
		return kvm_read_c0_guest_count(cop0);

	return kvm_mips_read_count_running(vcpu, ktime_get());
}