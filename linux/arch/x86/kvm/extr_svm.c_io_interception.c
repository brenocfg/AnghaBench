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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  io_exits; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;
struct vcpu_svm {struct kvm_vcpu vcpu; TYPE_3__* vmcb; int /*<<< orphan*/  next_rip; } ;
struct TYPE_5__ {int exit_info_1; int /*<<< orphan*/  exit_info_2; } ;
struct TYPE_6__ {TYPE_2__ control; } ;

/* Variables and functions */
 int SVM_IOIO_SIZE_MASK ; 
 int SVM_IOIO_SIZE_SHIFT ; 
 int SVM_IOIO_STR_MASK ; 
 int SVM_IOIO_TYPE_MASK ; 
 int kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_fast_pio (struct kvm_vcpu*,int,unsigned int,int) ; 

__attribute__((used)) static int io_interception(struct vcpu_svm *svm)
{
	struct kvm_vcpu *vcpu = &svm->vcpu;
	u32 io_info = svm->vmcb->control.exit_info_1; /* address size bug? */
	int size, in, string;
	unsigned port;

	++svm->vcpu.stat.io_exits;
	string = (io_info & SVM_IOIO_STR_MASK) != 0;
	in = (io_info & SVM_IOIO_TYPE_MASK) != 0;
	if (string)
		return kvm_emulate_instruction(vcpu, 0);

	port = io_info >> 16;
	size = (io_info & SVM_IOIO_SIZE_MASK) >> SVM_IOIO_SIZE_SHIFT;
	svm->next_rip = svm->vmcb->control.exit_info_2;

	return kvm_fast_pio(&svm->vcpu, size, port, in);
}