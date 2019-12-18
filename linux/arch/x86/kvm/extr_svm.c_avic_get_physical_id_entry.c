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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_svm {int /*<<< orphan*/  avic_physical_id_table_page; } ;

/* Variables and functions */
 unsigned int AVIC_MAX_PHYSICAL_ID_COUNT ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ ) ; 
 struct kvm_svm* to_kvm_svm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *avic_get_physical_id_entry(struct kvm_vcpu *vcpu,
				       unsigned int index)
{
	u64 *avic_physical_id_table;
	struct kvm_svm *kvm_svm = to_kvm_svm(vcpu->kvm);

	if (index >= AVIC_MAX_PHYSICAL_ID_COUNT)
		return NULL;

	avic_physical_id_table = page_address(kvm_svm->avic_physical_id_table_page);

	return &avic_physical_id_table[index];
}