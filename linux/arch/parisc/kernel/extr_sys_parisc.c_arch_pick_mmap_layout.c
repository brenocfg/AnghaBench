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
struct rlimit {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  get_unmapped_area; int /*<<< orphan*/  mmap_legacy_base; int /*<<< orphan*/  mmap_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_get_unmapped_area ; 
 int /*<<< orphan*/  arch_get_unmapped_area_topdown ; 
 scalar_t__ mmap_is_legacy () ; 
 int /*<<< orphan*/  mmap_legacy_base () ; 
 int /*<<< orphan*/  mmap_upper_limit (struct rlimit*) ; 

void arch_pick_mmap_layout(struct mm_struct *mm, struct rlimit *rlim_stack)
{
	mm->mmap_legacy_base = mmap_legacy_base();
	mm->mmap_base = mmap_upper_limit(rlim_stack);

	if (mmap_is_legacy()) {
		mm->mmap_base = mm->mmap_legacy_base;
		mm->get_unmapped_area = arch_get_unmapped_area;
	} else {
		mm->get_unmapped_area = arch_get_unmapped_area_topdown;
	}
}