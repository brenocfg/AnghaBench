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
struct TYPE_6__ {TYPE_2__* guest_fpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_fpu {int /*<<< orphan*/  xmm; int /*<<< orphan*/  last_dp; int /*<<< orphan*/  last_ip; int /*<<< orphan*/  last_opcode; int /*<<< orphan*/  ftwx; int /*<<< orphan*/  fsw; int /*<<< orphan*/  fcw; int /*<<< orphan*/  fpr; } ;
struct fxregs_state {int /*<<< orphan*/  xmm_space; int /*<<< orphan*/  rdp; int /*<<< orphan*/  rip; int /*<<< orphan*/  fop; int /*<<< orphan*/  twd; int /*<<< orphan*/  swd; int /*<<< orphan*/  cwd; int /*<<< orphan*/  st_space; } ;
struct TYPE_4__ {struct fxregs_state fxsave; } ;
struct TYPE_5__ {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_get_fpu(struct kvm_vcpu *vcpu, struct kvm_fpu *fpu)
{
	struct fxregs_state *fxsave;

	vcpu_load(vcpu);

	fxsave = &vcpu->arch.guest_fpu->state.fxsave;
	memcpy(fpu->fpr, fxsave->st_space, 128);
	fpu->fcw = fxsave->cwd;
	fpu->fsw = fxsave->swd;
	fpu->ftwx = fxsave->twd;
	fpu->last_opcode = fxsave->fop;
	fpu->last_ip = fxsave->rip;
	fpu->last_dp = fxsave->rdp;
	memcpy(fpu->xmm, fxsave->xmm_space, sizeof(fxsave->xmm_space));

	vcpu_put(vcpu);
	return 0;
}