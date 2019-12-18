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
struct task_struct {int dummy; } ;
struct TYPE_4__ {unsigned long sparc64_ctx_val; unsigned long hugetlb_pte_count; unsigned long thp_pte_count; TYPE_1__* tsb_block; int /*<<< orphan*/  tag_lock; int /*<<< orphan*/ * tag_store; int /*<<< orphan*/  lock; } ;
struct mm_struct {TYPE_2__ context; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tsb; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long HPAGE_SIZE ; 
 unsigned int MM_NUM_TSBS ; 
 size_t MM_TSB_BASE ; 
 size_t MM_TSB_HUGE ; 
 unsigned long PAGE_SIZE ; 
 unsigned long REAL_HPAGE_PER_HPAGE ; 
 unsigned long get_mm_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsb_grow (struct mm_struct*,size_t,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int init_new_context(struct task_struct *tsk, struct mm_struct *mm)
{
	unsigned long mm_rss = get_mm_rss(mm);
#if defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	unsigned long saved_hugetlb_pte_count;
	unsigned long saved_thp_pte_count;
#endif
	unsigned int i;

	spin_lock_init(&mm->context.lock);

	mm->context.sparc64_ctx_val = 0UL;

	mm->context.tag_store = NULL;
	spin_lock_init(&mm->context.tag_lock);

#if defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	/* We reset them to zero because the fork() page copying
	 * will re-increment the counters as the parent PTEs are
	 * copied into the child address space.
	 */
	saved_hugetlb_pte_count = mm->context.hugetlb_pte_count;
	saved_thp_pte_count = mm->context.thp_pte_count;
	mm->context.hugetlb_pte_count = 0;
	mm->context.thp_pte_count = 0;

	mm_rss -= saved_thp_pte_count * (HPAGE_SIZE / PAGE_SIZE);
#endif

	/* copy_mm() copies over the parent's mm_struct before calling
	 * us, so we need to zero out the TSB pointer or else tsb_grow()
	 * will be confused and think there is an older TSB to free up.
	 */
	for (i = 0; i < MM_NUM_TSBS; i++)
		mm->context.tsb_block[i].tsb = NULL;

	/* If this is fork, inherit the parent's TSB size.  We would
	 * grow it to that size on the first page fault anyways.
	 */
	tsb_grow(mm, MM_TSB_BASE, mm_rss);

#if defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	if (unlikely(saved_hugetlb_pte_count + saved_thp_pte_count))
		tsb_grow(mm, MM_TSB_HUGE,
			 (saved_hugetlb_pte_count + saved_thp_pte_count) *
			 REAL_HPAGE_PER_HPAGE);
#endif

	if (unlikely(!mm->context.tsb_block[MM_TSB_BASE].tsb))
		return -ENOMEM;

	return 0;
}