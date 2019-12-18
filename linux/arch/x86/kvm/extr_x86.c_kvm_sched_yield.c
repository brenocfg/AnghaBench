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
struct kvm_vcpu {int /*<<< orphan*/  ready; } ;
struct kvm_apic_map {unsigned long max_apic_id; TYPE_2__** phys_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  apic_map; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_4__ {struct kvm_vcpu* vcpu; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_yield_to (struct kvm_vcpu*) ; 
 scalar_t__ likely (struct kvm_apic_map*) ; 
 struct kvm_apic_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void kvm_sched_yield(struct kvm *kvm, unsigned long dest_id)
{
	struct kvm_vcpu *target = NULL;
	struct kvm_apic_map *map;

	rcu_read_lock();
	map = rcu_dereference(kvm->arch.apic_map);

	if (likely(map) && dest_id <= map->max_apic_id && map->phys_map[dest_id])
		target = map->phys_map[dest_id]->vcpu;

	rcu_read_unlock();

	if (target && READ_ONCE(target->ready))
		kvm_vcpu_yield_to(target);
}