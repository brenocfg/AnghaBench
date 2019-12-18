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
struct mmu_page_path {struct kvm_mmu_page** parent; } ;
struct kvm_mmu_pages {scalar_t__ nr; TYPE_2__* page; } ;
struct TYPE_3__ {int level; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;
struct TYPE_4__ {scalar_t__ idx; struct kvm_mmu_page* sp; } ;

/* Variables and functions */
 scalar_t__ INVALID_INDEX ; 
 int PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int mmu_pages_next (struct kvm_mmu_pages*,struct mmu_page_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmu_pages_first(struct kvm_mmu_pages *pvec,
			   struct mmu_page_path *parents)
{
	struct kvm_mmu_page *sp;
	int level;

	if (pvec->nr == 0)
		return 0;

	WARN_ON(pvec->page[0].idx != INVALID_INDEX);

	sp = pvec->page[0].sp;
	level = sp->role.level;
	WARN_ON(level == PT_PAGE_TABLE_LEVEL);

	parents->parent[level-2] = sp;

	/* Also set up a sentinel.  Further entries in pvec are all
	 * children of sp, so this element is never overwritten.
	 */
	parents->parent[level-1] = NULL;
	return mmu_pages_next(pvec, parents, 0);
}