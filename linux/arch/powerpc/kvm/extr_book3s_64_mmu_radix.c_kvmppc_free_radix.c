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
struct TYPE_2__ {int /*<<< orphan*/ * pgtable; int /*<<< orphan*/  lpid; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_free_pgtable_radix (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvmppc_free_radix(struct kvm *kvm)
{
	if (kvm->arch.pgtable) {
		kvmppc_free_pgtable_radix(kvm, kvm->arch.pgtable,
					  kvm->arch.lpid);
		pgd_free(kvm->mm, kvm->arch.pgtable);
		kvm->arch.pgtable = NULL;
	}
}