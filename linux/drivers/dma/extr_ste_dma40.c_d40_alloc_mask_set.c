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
struct d40_phy_res {int allocated_src; int allocated_dst; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BIT (int) ; 
 int D40_ALLOC_FREE ; 
 void* D40_ALLOC_LOG_FREE ; 
 void* D40_ALLOC_PHY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool d40_alloc_mask_set(struct d40_phy_res *phy,
			       bool is_src, int log_event_line, bool is_log,
			       bool *first_user)
{
	unsigned long flags;
	spin_lock_irqsave(&phy->lock, flags);

	*first_user = ((phy->allocated_src | phy->allocated_dst)
			== D40_ALLOC_FREE);

	if (!is_log) {
		/* Physical interrupts are masked per physical full channel */
		if (phy->allocated_src == D40_ALLOC_FREE &&
		    phy->allocated_dst == D40_ALLOC_FREE) {
			phy->allocated_dst = D40_ALLOC_PHY;
			phy->allocated_src = D40_ALLOC_PHY;
			goto found_unlock;
		} else
			goto not_found_unlock;
	}

	/* Logical channel */
	if (is_src) {
		if (phy->allocated_src == D40_ALLOC_PHY)
			goto not_found_unlock;

		if (phy->allocated_src == D40_ALLOC_FREE)
			phy->allocated_src = D40_ALLOC_LOG_FREE;

		if (!(phy->allocated_src & BIT(log_event_line))) {
			phy->allocated_src |= BIT(log_event_line);
			goto found_unlock;
		} else
			goto not_found_unlock;
	} else {
		if (phy->allocated_dst == D40_ALLOC_PHY)
			goto not_found_unlock;

		if (phy->allocated_dst == D40_ALLOC_FREE)
			phy->allocated_dst = D40_ALLOC_LOG_FREE;

		if (!(phy->allocated_dst & BIT(log_event_line))) {
			phy->allocated_dst |= BIT(log_event_line);
			goto found_unlock;
		}
	}
 not_found_unlock:
	spin_unlock_irqrestore(&phy->lock, flags);
	return false;
 found_unlock:
	spin_unlock_irqrestore(&phy->lock, flags);
	return true;
}