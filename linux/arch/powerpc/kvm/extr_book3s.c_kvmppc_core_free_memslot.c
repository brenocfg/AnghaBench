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
struct kvm_memory_slot {int dummy; } ;
struct TYPE_4__ {TYPE_1__* kvm_ops; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_memslot ) (struct kvm_memory_slot*,struct kvm_memory_slot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct kvm_memory_slot*,struct kvm_memory_slot*) ; 

void kvmppc_core_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free,
			      struct kvm_memory_slot *dont)
{
	kvm->arch.kvm_ops->free_memslot(free, dont);
}