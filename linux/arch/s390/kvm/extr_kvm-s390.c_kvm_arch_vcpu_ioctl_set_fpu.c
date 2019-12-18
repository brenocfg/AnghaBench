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
struct kvm_vcpu {TYPE_2__* run; } ;
struct kvm_fpu {scalar_t__ fprs; int /*<<< orphan*/  fpc; } ;
typedef  int /*<<< orphan*/  freg_t ;
typedef  int /*<<< orphan*/  __vector128 ;
struct TYPE_6__ {int /*<<< orphan*/  fprs; scalar_t__ vrs; int /*<<< orphan*/  fpc; } ;
struct TYPE_4__ {TYPE_3__ regs; } ;
struct TYPE_5__ {TYPE_1__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MACHINE_HAS_VX ; 
 int /*<<< orphan*/  convert_fp_to_vx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ test_fp_ctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
{
	int ret = 0;

	vcpu_load(vcpu);

	if (test_fp_ctl(fpu->fpc)) {
		ret = -EINVAL;
		goto out;
	}
	vcpu->run->s.regs.fpc = fpu->fpc;
	if (MACHINE_HAS_VX)
		convert_fp_to_vx((__vector128 *) vcpu->run->s.regs.vrs,
				 (freg_t *) fpu->fprs);
	else
		memcpy(vcpu->run->s.regs.fprs, &fpu->fprs, sizeof(fpu->fprs));

out:
	vcpu_put(vcpu);
	return ret;
}