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
struct TYPE_5__ {int /*<<< orphan*/  bd_emupage_lock; scalar_t__ bd_emupage_allocmap; int /*<<< orphan*/  bd_emupage_queue; } ;
typedef  TYPE_2__ mm_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  pid; TYPE_1__* mm; } ;
struct TYPE_4__ {TYPE_2__ context; } ;

/* Variables and functions */
 int BD_EMUFRAME_NONE ; 
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int bitmap_find_free_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_full (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  emupage_frame_count ; 
 scalar_t__ kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_killable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alloc_emuframe(void)
{
	mm_context_t *mm_ctx = &current->mm->context;
	int idx;

retry:
	spin_lock(&mm_ctx->bd_emupage_lock);

	/* Ensure we have an allocation bitmap */
	if (!mm_ctx->bd_emupage_allocmap) {
		mm_ctx->bd_emupage_allocmap =
			kcalloc(BITS_TO_LONGS(emupage_frame_count),
					      sizeof(unsigned long),
				GFP_ATOMIC);

		if (!mm_ctx->bd_emupage_allocmap) {
			idx = BD_EMUFRAME_NONE;
			goto out_unlock;
		}
	}

	/* Attempt to allocate a single bit/frame */
	idx = bitmap_find_free_region(mm_ctx->bd_emupage_allocmap,
				      emupage_frame_count, 0);
	if (idx < 0) {
		/*
		 * Failed to allocate a frame. We'll wait until one becomes
		 * available. We unlock the page so that other threads actually
		 * get the opportunity to free their frames, which means
		 * technically the result of bitmap_full may be incorrect.
		 * However the worst case is that we repeat all this and end up
		 * back here again.
		 */
		spin_unlock(&mm_ctx->bd_emupage_lock);
		if (!wait_event_killable(mm_ctx->bd_emupage_queue,
			!bitmap_full(mm_ctx->bd_emupage_allocmap,
				     emupage_frame_count)))
			goto retry;

		/* Received a fatal signal - just give in */
		return BD_EMUFRAME_NONE;
	}

	/* Success! */
	pr_debug("allocate emuframe %d to %d\n", idx, current->pid);
out_unlock:
	spin_unlock(&mm_ctx->bd_emupage_lock);
	return idx;
}