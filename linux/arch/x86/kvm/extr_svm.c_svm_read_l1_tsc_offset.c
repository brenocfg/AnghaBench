#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {TYPE_2__* hsave; } ;
struct vcpu_svm {TYPE_3__ nested; } ;
struct TYPE_8__ {int /*<<< orphan*/  tsc_offset; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  tsc_offset; } ;
struct TYPE_6__ {TYPE_1__ control; } ;

/* Variables and functions */
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static u64 svm_read_l1_tsc_offset(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	if (is_guest_mode(vcpu))
		return svm->nested.hsave->control.tsc_offset;

	return vcpu->arch.tsc_offset;
}