#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * gpr; } ;
struct TYPE_4__ {TYPE_1__ regs; int /*<<< orphan*/  pgdir; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 long kvmppc_do_h_enter (int /*<<< orphan*/ ,unsigned long,long,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

long kvmppc_h_enter(struct kvm_vcpu *vcpu, unsigned long flags,
		    long pte_index, unsigned long pteh, unsigned long ptel)
{
	return kvmppc_do_h_enter(vcpu->kvm, flags, pte_index, pteh, ptel,
				 vcpu->arch.pgdir, true,
				 &vcpu->arch.regs.gpr[4]);
}