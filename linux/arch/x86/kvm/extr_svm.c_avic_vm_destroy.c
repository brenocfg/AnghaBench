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
struct kvm_svm {int /*<<< orphan*/  hnode; scalar_t__ avic_physical_id_table_page; scalar_t__ avic_logical_id_table_page; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  avic ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  svm_vm_data_hash_lock ; 
 struct kvm_svm* to_kvm_svm (struct kvm*) ; 

__attribute__((used)) static void avic_vm_destroy(struct kvm *kvm)
{
	unsigned long flags;
	struct kvm_svm *kvm_svm = to_kvm_svm(kvm);

	if (!avic)
		return;

	if (kvm_svm->avic_logical_id_table_page)
		__free_page(kvm_svm->avic_logical_id_table_page);
	if (kvm_svm->avic_physical_id_table_page)
		__free_page(kvm_svm->avic_physical_id_table_page);

	spin_lock_irqsave(&svm_vm_data_hash_lock, flags);
	hash_del(&kvm_svm->hnode);
	spin_unlock_irqrestore(&svm_vm_data_hash_lock, flags);
}