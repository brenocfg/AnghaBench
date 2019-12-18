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
struct TYPE_3__ {int /*<<< orphan*/  linear_rip; } ;
struct TYPE_4__ {int /*<<< orphan*/  complete_userspace_io; TYPE_1__ pio; int /*<<< orphan*/  emulate_ctxt; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_fast_pio_in ; 
 int emulator_pio_in_emulated (int /*<<< orphan*/ *,int,unsigned short,unsigned long*,int) ; 
 int /*<<< orphan*/  kvm_get_linear_rip (struct kvm_vcpu*) ; 
 unsigned long kvm_rax_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rax_write (struct kvm_vcpu*,unsigned long) ; 

__attribute__((used)) static int kvm_fast_pio_in(struct kvm_vcpu *vcpu, int size,
			   unsigned short port)
{
	unsigned long val;
	int ret;

	/* For size less than 4 we merge, else we zero extend */
	val = (size < 4) ? kvm_rax_read(vcpu) : 0;

	ret = emulator_pio_in_emulated(&vcpu->arch.emulate_ctxt, size, port,
				       &val, 1);
	if (ret) {
		kvm_rax_write(vcpu, val);
		return ret;
	}

	vcpu->arch.pio.linear_rip = kvm_get_linear_rip(vcpu);
	vcpu->arch.complete_userspace_io = complete_fast_pio_in;

	return 0;
}