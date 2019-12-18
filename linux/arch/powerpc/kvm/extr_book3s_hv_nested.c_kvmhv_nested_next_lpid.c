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
struct TYPE_2__ {int max_nested_lpid; scalar_t__* nested_guests; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvmhv_nested_next_lpid(struct kvm *kvm, int lpid)
{
	int ret = -1;

	spin_lock(&kvm->mmu_lock);
	while (++lpid <= kvm->arch.max_nested_lpid) {
		if (kvm->arch.nested_guests[lpid]) {
			ret = lpid;
			break;
		}
	}
	spin_unlock(&kvm->mmu_lock);
	return ret;
}