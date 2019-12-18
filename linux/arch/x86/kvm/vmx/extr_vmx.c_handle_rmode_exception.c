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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ halt_request; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int GP_VECTOR ; 
 int SS_VECTOR ; 
 scalar_t__ kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int) ; 
 int kvm_vcpu_halt (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_rmode_exception(struct kvm_vcpu *vcpu,
				  int vec, u32 err_code)
{
	/*
	 * Instruction with address size override prefix opcode 0x67
	 * Cause the #SS fault with 0 error code in VM86 mode.
	 */
	if (((vec == GP_VECTOR) || (vec == SS_VECTOR)) && err_code == 0) {
		if (kvm_emulate_instruction(vcpu, 0)) {
			if (vcpu->arch.halt_request) {
				vcpu->arch.halt_request = 0;
				return kvm_vcpu_halt(vcpu);
			}
			return 1;
		}
		return 0;
	}

	/*
	 * Forward all other exceptions that are valid in real mode.
	 * FIXME: Breaks guest debugging in real mode, needs to be fixed with
	 *        the required debugging infrastructure rework.
	 */
	kvm_queue_exception(vcpu, vec);
	return 1;
}