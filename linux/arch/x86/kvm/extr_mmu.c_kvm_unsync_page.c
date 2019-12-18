#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_mmu_page {int unsync; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmu_unsync; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_mark_parents_unsync (struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  trace_kvm_mmu_unsync_page (struct kvm_mmu_page*) ; 

__attribute__((used)) static void kvm_unsync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp)
{
	trace_kvm_mmu_unsync_page(sp);
	++vcpu->kvm->stat.mmu_unsync;
	sp->unsync = 1;

	kvm_mmu_mark_parents_unsync(sp);
}