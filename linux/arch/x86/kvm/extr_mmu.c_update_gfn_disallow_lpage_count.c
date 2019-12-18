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
struct kvm_lpage_info {scalar_t__ disallow_lpage; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int PT_DIRECTORY_LEVEL ; 
 int PT_MAX_HUGEPAGE_LEVEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct kvm_lpage_info* lpage_info_slot (int /*<<< orphan*/ ,struct kvm_memory_slot*,int) ; 

__attribute__((used)) static void update_gfn_disallow_lpage_count(struct kvm_memory_slot *slot,
					    gfn_t gfn, int count)
{
	struct kvm_lpage_info *linfo;
	int i;

	for (i = PT_DIRECTORY_LEVEL; i <= PT_MAX_HUGEPAGE_LEVEL; ++i) {
		linfo = lpage_info_slot(gfn, slot, i);
		linfo->disallow_lpage += count;
		WARN_ON(linfo->disallow_lpage < 0);
	}
}