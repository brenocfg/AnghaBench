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
struct kvm_mmu_page {int lpage_disallowed; int /*<<< orphan*/  lpage_disallowed_link; } ;
struct TYPE_2__ {int /*<<< orphan*/  nx_lpage_splits; } ;
struct kvm {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unaccount_huge_nx_page(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	--kvm->stat.nx_lpage_splits;
	sp->lpage_disallowed = false;
	list_del(&sp->lpage_disallowed_link);
}