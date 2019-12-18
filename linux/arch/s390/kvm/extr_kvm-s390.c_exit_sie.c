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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int prog0c; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_STOP_INT ; 
 int PROG_IN_SIE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  kvm_s390_set_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_vsie_kick (struct kvm_vcpu*) ; 

void exit_sie(struct kvm_vcpu *vcpu)
{
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_STOP_INT);
	kvm_s390_vsie_kick(vcpu);
	while (vcpu->arch.sie_block->prog0c & PROG_IN_SIE)
		cpu_relax();
}