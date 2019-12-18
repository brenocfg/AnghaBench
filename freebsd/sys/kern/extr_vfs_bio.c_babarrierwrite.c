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
struct buf {int b_flags; } ;

/* Variables and functions */
 int B_ASYNC ; 
 int B_BARRIER ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 

void
babarrierwrite(struct buf *bp)
{

	bp->b_flags |= B_ASYNC | B_BARRIER;
	(void) bwrite(bp);
}