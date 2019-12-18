#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct kvm_pit_state2 {int flags; int /*<<< orphan*/  channels; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  lock; TYPE_3__* channels; } ;
struct kvm_pit {TYPE_2__ pit_state; } ;
struct TYPE_4__ {struct kvm_pit* vpit; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int KVM_PIT_FLAGS_HPET_LEGACY ; 
 int /*<<< orphan*/  kvm_pit_load_count (struct kvm_pit*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_pit2(struct kvm *kvm, struct kvm_pit_state2 *ps)
{
	int start = 0;
	int i;
	u32 prev_legacy, cur_legacy;
	struct kvm_pit *pit = kvm->arch.vpit;

	mutex_lock(&pit->pit_state.lock);
	prev_legacy = pit->pit_state.flags & KVM_PIT_FLAGS_HPET_LEGACY;
	cur_legacy = ps->flags & KVM_PIT_FLAGS_HPET_LEGACY;
	if (!prev_legacy && cur_legacy)
		start = 1;
	memcpy(&pit->pit_state.channels, &ps->channels,
	       sizeof(pit->pit_state.channels));
	pit->pit_state.flags = ps->flags;
	for (i = 0; i < 3; i++)
		kvm_pit_load_count(pit, i, pit->pit_state.channels[i].count,
				   start && i == 0);
	mutex_unlock(&pit->pit_state.lock);
	return 0;
}