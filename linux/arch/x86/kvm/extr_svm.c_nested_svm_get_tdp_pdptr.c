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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  nested_cr3; } ;
struct vcpu_svm {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sme_clr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpa_to_gfn (int /*<<< orphan*/ ) ; 
 int kvm_vcpu_read_guest_page (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ offset_in_page (int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static u64 nested_svm_get_tdp_pdptr(struct kvm_vcpu *vcpu, int index)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	u64 cr3 = svm->nested.nested_cr3;
	u64 pdpte;
	int ret;

	ret = kvm_vcpu_read_guest_page(vcpu, gpa_to_gfn(__sme_clr(cr3)), &pdpte,
				       offset_in_page(cr3) + index * 8, 8);
	if (ret)
		return 0;
	return pdpte;
}