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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_shadow_all ) (struct kvm*) ;} ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int handle_hva_to_gpa (struct kvm*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  kvm_set_spte_handler ; 
 int /*<<< orphan*/  stub1 (struct kvm*) ; 

int kvm_set_spte_hva(struct kvm *kvm, unsigned long hva, pte_t pte)
{
	unsigned long end = hva + PAGE_SIZE;
	int ret;

	ret = handle_hva_to_gpa(kvm, hva, end, &kvm_set_spte_handler, &pte);
	if (ret)
		kvm_mips_callbacks->flush_shadow_all(kvm);
	return 0;
}