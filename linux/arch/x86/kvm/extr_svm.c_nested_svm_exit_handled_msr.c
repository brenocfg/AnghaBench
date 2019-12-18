#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {unsigned long long intercept; scalar_t__ vmcb_msrpm; } ;
struct TYPE_6__ {int* regs; } ;
struct TYPE_10__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_4__ nested; TYPE_5__ vcpu; TYPE_3__* vmcb; } ;
struct TYPE_7__ {int exit_info_1; } ;
struct TYPE_8__ {TYPE_2__ control; } ;

/* Variables and functions */
 unsigned long long INTERCEPT_MSR_PROT ; 
 int MSR_INVALID ; 
 int NESTED_EXIT_DONE ; 
 int NESTED_EXIT_HOST ; 
 size_t VCPU_REGS_RCX ; 
 scalar_t__ kvm_vcpu_read_guest (TYPE_5__*,scalar_t__,int*,int) ; 
 int svm_msrpm_offset (int) ; 

__attribute__((used)) static int nested_svm_exit_handled_msr(struct vcpu_svm *svm)
{
	u32 offset, msr, value;
	int write, mask;

	if (!(svm->nested.intercept & (1ULL << INTERCEPT_MSR_PROT)))
		return NESTED_EXIT_HOST;

	msr    = svm->vcpu.arch.regs[VCPU_REGS_RCX];
	offset = svm_msrpm_offset(msr);
	write  = svm->vmcb->control.exit_info_1 & 1;
	mask   = 1 << ((2 * (msr & 0xf)) + write);

	if (offset == MSR_INVALID)
		return NESTED_EXIT_DONE;

	/* Offset is in 32 bit units but need in 8 bit units */
	offset *= 4;

	if (kvm_vcpu_read_guest(&svm->vcpu, svm->nested.vmcb_msrpm + offset, &value, 4))
		return NESTED_EXIT_DONE;

	return (value & mask) ? NESTED_EXIT_DONE : NESTED_EXIT_HOST;
}