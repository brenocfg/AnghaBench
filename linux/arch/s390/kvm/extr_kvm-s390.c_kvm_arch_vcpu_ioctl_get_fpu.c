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
struct kvm_vcpu {TYPE_3__* run; } ;
struct kvm_fpu {int /*<<< orphan*/  fpc; scalar_t__ fprs; } ;
typedef  int /*<<< orphan*/  freg_t ;
typedef  int /*<<< orphan*/  __vector128 ;
struct TYPE_4__ {int /*<<< orphan*/  fpc; int /*<<< orphan*/  fprs; scalar_t__ vrs; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;
struct TYPE_6__ {TYPE_2__ s; } ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_VX ; 
 int /*<<< orphan*/  convert_vx_to_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
{
	vcpu_load(vcpu);

	/* make sure we have the latest values */
	save_fpu_regs();
	if (MACHINE_HAS_VX)
		convert_vx_to_fp((freg_t *) fpu->fprs,
				 (__vector128 *) vcpu->run->s.regs.vrs);
	else
		memcpy(fpu->fprs, vcpu->run->s.regs.fprs, sizeof(fpu->fprs));
	fpu->fpc = vcpu->run->s.regs.fpc;

	vcpu_put(vcpu);
	return 0;
}