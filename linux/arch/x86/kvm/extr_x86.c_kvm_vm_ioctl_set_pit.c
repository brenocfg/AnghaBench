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
struct kvm_pit_state {TYPE_1__* channels; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  channels; } ;
struct kvm_pit {TYPE_3__ pit_state; } ;
struct TYPE_5__ {struct kvm_pit* vpit; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_pit_load_count (struct kvm_pit*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct kvm_pit_state*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_pit(struct kvm *kvm, struct kvm_pit_state *ps)
{
	int i;
	struct kvm_pit *pit = kvm->arch.vpit;

	mutex_lock(&pit->pit_state.lock);
	memcpy(&pit->pit_state.channels, ps, sizeof(*ps));
	for (i = 0; i < 3; i++)
		kvm_pit_load_count(pit, i, ps->channels[i].count, 0);
	mutex_unlock(&pit->pit_state.lock);
	return 0;
}