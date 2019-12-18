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
typedef  scalar_t__ daddr_t ;
struct TYPE_9__ {int /*<<< orphan*/  swp_blks; scalar_t__ writemappings; } ;
struct TYPE_10__ {TYPE_1__ swp; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ un_pager; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_NOWAIT ; 
 int M_USE_RESERVE ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ SWAPBLK_NONE ; 
 int SWAP_META_PAGES ; 
 int SWAP_PCTRIE_INSERT (int /*<<< orphan*/ *,struct swblk*) ; 
 struct swblk* SWAP_PCTRIE_LOOKUP (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OOM_SWAPZ ; 
 scalar_t__ atomic_cmpset_int (int volatile*,int,int) ; 
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 scalar_t__ curproc ; 
 scalar_t__ pageproc ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  pctrie_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rounddown (scalar_t__,int) ; 
 int /*<<< orphan*/  swblk_zone ; 
 int /*<<< orphan*/  swp_pager_free_empty_swblk (TYPE_3__*,struct swblk*) ; 
 int /*<<< orphan*/  swpctrie_zone ; 
 struct swblk* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct swblk*) ; 
 scalar_t__ uma_zone_exhausted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zwait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pageout_oom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static daddr_t
swp_pager_meta_build(vm_object_t object, vm_pindex_t pindex, daddr_t swapblk)
{
	static volatile int swblk_zone_exhausted, swpctrie_zone_exhausted;
	struct swblk *sb, *sb1;
	vm_pindex_t modpi, rdpi;
	daddr_t prev_swapblk;
	int error, i;

	VM_OBJECT_ASSERT_WLOCKED(object);

	/*
	 * Convert default object to swap object if necessary
	 */
	if (object->type != OBJT_SWAP) {
		pctrie_init(&object->un_pager.swp.swp_blks);

		/*
		 * Ensure that swap_pager_swapoff()'s iteration over
		 * object_list does not see a garbage pctrie.
		 */
		atomic_thread_fence_rel();

		object->type = OBJT_SWAP;
		object->un_pager.swp.writemappings = 0;
		KASSERT(object->handle == NULL, ("default pager with handle"));
	}

	rdpi = rounddown(pindex, SWAP_META_PAGES);
	sb = SWAP_PCTRIE_LOOKUP(&object->un_pager.swp.swp_blks, rdpi);
	if (sb == NULL) {
		if (swapblk == SWAPBLK_NONE)
			return (SWAPBLK_NONE);
		for (;;) {
			sb = uma_zalloc(swblk_zone, M_NOWAIT | (curproc ==
			    pageproc ? M_USE_RESERVE : 0));
			if (sb != NULL) {
				sb->p = rdpi;
				for (i = 0; i < SWAP_META_PAGES; i++)
					sb->d[i] = SWAPBLK_NONE;
				if (atomic_cmpset_int(&swblk_zone_exhausted,
				    1, 0))
					printf("swblk zone ok\n");
				break;
			}
			VM_OBJECT_WUNLOCK(object);
			if (uma_zone_exhausted(swblk_zone)) {
				if (atomic_cmpset_int(&swblk_zone_exhausted,
				    0, 1))
					printf("swap blk zone exhausted, "
					    "increase kern.maxswzone\n");
				vm_pageout_oom(VM_OOM_SWAPZ);
				pause("swzonxb", 10);
			} else
				uma_zwait(swblk_zone);
			VM_OBJECT_WLOCK(object);
			sb = SWAP_PCTRIE_LOOKUP(&object->un_pager.swp.swp_blks,
			    rdpi);
			if (sb != NULL)
				/*
				 * Somebody swapped out a nearby page,
				 * allocating swblk at the rdpi index,
				 * while we dropped the object lock.
				 */
				goto allocated;
		}
		for (;;) {
			error = SWAP_PCTRIE_INSERT(
			    &object->un_pager.swp.swp_blks, sb);
			if (error == 0) {
				if (atomic_cmpset_int(&swpctrie_zone_exhausted,
				    1, 0))
					printf("swpctrie zone ok\n");
				break;
			}
			VM_OBJECT_WUNLOCK(object);
			if (uma_zone_exhausted(swpctrie_zone)) {
				if (atomic_cmpset_int(&swpctrie_zone_exhausted,
				    0, 1))
					printf("swap pctrie zone exhausted, "
					    "increase kern.maxswzone\n");
				vm_pageout_oom(VM_OOM_SWAPZ);
				pause("swzonxp", 10);
			} else
				uma_zwait(swpctrie_zone);
			VM_OBJECT_WLOCK(object);
			sb1 = SWAP_PCTRIE_LOOKUP(&object->un_pager.swp.swp_blks,
			    rdpi);
			if (sb1 != NULL) {
				uma_zfree(swblk_zone, sb);
				sb = sb1;
				goto allocated;
			}
		}
	}
allocated:
	MPASS(sb->p == rdpi);

	modpi = pindex % SWAP_META_PAGES;
	/* Return prior contents of metadata. */
	prev_swapblk = sb->d[modpi];
	/* Enter block into metadata. */
	sb->d[modpi] = swapblk;

	/*
	 * Free the swblk if we end up with the empty page run.
	 */
	if (swapblk == SWAPBLK_NONE)
	    swp_pager_free_empty_swblk(object, sb);
	return (prev_swapblk);
}