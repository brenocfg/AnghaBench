#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_svm {scalar_t__ dfr_reg; int /*<<< orphan*/  ldr_reg; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ APIC_DFR_FLAT ; 
 int /*<<< orphan*/  AVIC_LOGICAL_ID_ENTRY_VALID_BIT ; 
 int /*<<< orphan*/ * avic_get_logical_id_entry (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void avic_invalidate_logical_id_entry(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	bool flat = svm->dfr_reg == APIC_DFR_FLAT;
	u32 *entry = avic_get_logical_id_entry(vcpu, svm->ldr_reg, flat);

	if (entry)
		clear_bit(AVIC_LOGICAL_ID_ENTRY_VALID_BIT, (unsigned long *)entry);
}