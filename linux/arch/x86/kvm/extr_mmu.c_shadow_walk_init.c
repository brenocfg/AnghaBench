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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_shadow_walk_iterator {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  root_hpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  shadow_walk_init_using_root (struct kvm_shadow_walk_iterator*,struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shadow_walk_init(struct kvm_shadow_walk_iterator *iterator,
			     struct kvm_vcpu *vcpu, u64 addr)
{
	shadow_walk_init_using_root(iterator, vcpu, vcpu->arch.mmu->root_hpa,
				    addr);
}