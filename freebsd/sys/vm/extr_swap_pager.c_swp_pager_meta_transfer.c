#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_3__* vm_object_t ;
struct swblk {scalar_t__ p; scalar_t__* d; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_9__ {int /*<<< orphan*/  swp_blks; } ;
struct TYPE_10__ {TYPE_1__ swp; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ un_pager; } ;

/* Variables and functions */
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ SWAPBLK_NONE ; 
 scalar_t__ SWAP_META_PAGES ; 
 struct swblk* SWAP_PCTRIE_LOOKUP_GE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_PCTRIE_REMOVE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_3__*) ; 
 int /*<<< orphan*/  rounddown (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  swblk_zone ; 
 int /*<<< orphan*/  swp_pager_freeswapspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_pager_init_freerange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ swp_pager_swblk_empty (struct swblk*,int,scalar_t__) ; 
 int /*<<< orphan*/  swp_pager_update_freerange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  swp_pager_xfer_source (TYPE_3__*,TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct swblk*) ; 

__attribute__((used)) static void
swp_pager_meta_transfer(vm_object_t srcobject, vm_object_t dstobject,
    vm_pindex_t pindex, vm_pindex_t count)
{
	struct swblk *sb;
	daddr_t n_free, s_free;
	vm_pindex_t offset, last;
	int i, limit, start;

	VM_OBJECT_ASSERT_WLOCKED(srcobject);
	if (srcobject->type != OBJT_SWAP || count == 0)
		return;

	swp_pager_init_freerange(&s_free, &n_free);
	offset = pindex;
	last = pindex + count;
	for (;;) {
		sb = SWAP_PCTRIE_LOOKUP_GE(&srcobject->un_pager.swp.swp_blks,
		    rounddown(pindex, SWAP_META_PAGES));
		if (sb == NULL || sb->p >= last)
			break;
		start = pindex > sb->p ? pindex - sb->p : 0;
		limit = last - sb->p < SWAP_META_PAGES ? last - sb->p :
		    SWAP_META_PAGES;
		for (i = start; i < limit; i++) {
			if (sb->d[i] == SWAPBLK_NONE)
				continue;
			if (dstobject == NULL ||
			    !swp_pager_xfer_source(srcobject, dstobject, 
			    sb->p + i - offset, sb->d[i])) {
				swp_pager_update_freerange(&s_free, &n_free,
				    sb->d[i]);
			}
			sb->d[i] = SWAPBLK_NONE;
		}
		pindex = sb->p + SWAP_META_PAGES;
		if (swp_pager_swblk_empty(sb, 0, start) &&
		    swp_pager_swblk_empty(sb, limit, SWAP_META_PAGES)) {
			SWAP_PCTRIE_REMOVE(&srcobject->un_pager.swp.swp_blks,
			    sb->p);
			uma_zfree(swblk_zone, sb);
		}
	}
	swp_pager_freeswapspace(s_free, n_free);
}