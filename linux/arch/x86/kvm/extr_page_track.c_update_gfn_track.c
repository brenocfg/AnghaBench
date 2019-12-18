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
struct TYPE_2__ {int** gfn_track; } ;
struct kvm_memory_slot {TYPE_1__ arch; int /*<<< orphan*/  base_gfn; } ;
typedef  int /*<<< orphan*/  gfn_t ;
typedef  enum kvm_page_track_mode { ____Placeholder_kvm_page_track_mode } kvm_page_track_mode ;

/* Variables and functions */
 int /*<<< orphan*/  PT_PAGE_TABLE_LEVEL ; 
 int USHRT_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int gfn_to_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_gfn_track(struct kvm_memory_slot *slot, gfn_t gfn,
			     enum kvm_page_track_mode mode, short count)
{
	int index, val;

	index = gfn_to_index(gfn, slot->base_gfn, PT_PAGE_TABLE_LEVEL);

	val = slot->arch.gfn_track[mode][index];

	if (WARN_ON(val + count < 0 || val + count > USHRT_MAX))
		return;

	slot->arch.gfn_track[mode][index] += count;
}