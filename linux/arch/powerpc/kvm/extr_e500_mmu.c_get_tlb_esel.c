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
struct kvmppc_vcpu_e500 {TYPE_1__* gtlb_params; } ;
struct TYPE_6__ {TYPE_2__* shared; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  mas2; } ;
struct TYPE_4__ {int ways; int entries; } ;

/* Variables and functions */
 int get_tlb_esel_bit (struct kvm_vcpu*) ; 
 scalar_t__ gtlb0_set_base (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned int get_tlb_esel(struct kvm_vcpu *vcpu, int tlbsel)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int esel = get_tlb_esel_bit(vcpu);

	if (tlbsel == 0) {
		esel &= vcpu_e500->gtlb_params[0].ways - 1;
		esel += gtlb0_set_base(vcpu_e500, vcpu->arch.shared->mas2);
	} else {
		esel &= vcpu_e500->gtlb_params[tlbsel].entries - 1;
	}

	return esel;
}