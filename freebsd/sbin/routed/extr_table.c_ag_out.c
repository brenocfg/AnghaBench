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
struct ag_info {int ag_state; int ag_mask; int ag_dst_h; struct ag_info* ag_cors; } ;
typedef  int naddr ;

/* Variables and functions */
 int AGS_REDUN0 ; 
 int AGS_REDUN1 ; 
 int AGS_SPLIT_HZ ; 

__attribute__((used)) static void
ag_out(struct ag_info *ag,
	 void (*out)(struct ag_info *))
{
	struct ag_info *ag_cors;
	naddr bit;


	/* Forget it if this route should not be output for split-horizon. */
	if (ag->ag_state & AGS_SPLIT_HZ)
		return;

	/* If we output both the even and odd twins, then the immediate parent,
	 * if it is present, is redundant, unless the parent manages to
	 * aggregate into something coarser.
	 * On successive calls, this code detects the even and odd twins,
	 * and marks the parent.
	 *
	 * Note that the order in which the radix tree code emits routes
	 * ensures that the twins are seen before the parent is emitted.
	 */
	ag_cors = ag->ag_cors;
	if (ag_cors != NULL
	    && ag_cors->ag_mask == ag->ag_mask<<1
	    && ag_cors->ag_dst_h == (ag->ag_dst_h & ag_cors->ag_mask)) {
		ag_cors->ag_state |= ((ag_cors->ag_dst_h == ag->ag_dst_h)
				      ? AGS_REDUN0
				      : AGS_REDUN1);
	}

	/* Skip it if this route is itself redundant.
	 *
	 * It is ok to change the contents of the slot here, since it is
	 * always deleted next.
	 */
	if (ag->ag_state & AGS_REDUN0) {
		if (ag->ag_state & AGS_REDUN1)
			return;		/* quit if fully redundant */
		/* make it finer if it is half-redundant */
		bit = (-ag->ag_mask) >> 1;
		ag->ag_dst_h |= bit;
		ag->ag_mask |= bit;

	} else if (ag->ag_state & AGS_REDUN1) {
		/* make it finer if it is half-redundant */
		bit = (-ag->ag_mask) >> 1;
		ag->ag_mask |= bit;
	}
	out(ag);
}