#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_memory_slot {int dummy; } ;
struct kvm_lpage_info {int /*<<< orphan*/  disallow_lpage; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 struct kvm_lpage_info* lpage_info_slot (int /*<<< orphan*/ ,struct kvm_memory_slot*,int) ; 

__attribute__((used)) static bool __mmu_gfn_lpage_is_disallowed(gfn_t gfn, int level,
					  struct kvm_memory_slot *slot)
{
	struct kvm_lpage_info *linfo;

	if (slot) {
		linfo = lpage_info_slot(gfn, slot, level);
		return !!linfo->disallow_lpage;
	}

	return true;
}