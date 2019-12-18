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
typedef  int u32 ;
struct TYPE_2__ {int pc; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEF_BD ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int kvm_compute_return_epc (struct kvm_vcpu*,int,int*) ; 
 int /*<<< orphan*/  kvm_debug (char*,int) ; 

enum emulation_result update_pc(struct kvm_vcpu *vcpu, u32 cause)
{
	int err;

	if (cause & CAUSEF_BD) {
		err = kvm_compute_return_epc(vcpu, vcpu->arch.pc,
					     &vcpu->arch.pc);
		if (err)
			return EMULATE_FAIL;
	} else {
		vcpu->arch.pc += 4;
	}

	kvm_debug("update_pc(): New PC: %#lx\n", vcpu->arch.pc);

	return EMULATE_DONE;
}