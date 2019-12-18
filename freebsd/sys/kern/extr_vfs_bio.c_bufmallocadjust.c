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
struct buf {int b_flags; int b_bufsize; } ;

/* Variables and functions */
 int B_MALLOC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufmallocspace ; 

__attribute__((used)) static void
bufmallocadjust(struct buf *bp, int bufsize)
{
	int diff;

	KASSERT((bp->b_flags & B_MALLOC) != 0,
	    ("bufmallocadjust: non-malloc buf %p", bp));
	diff = bufsize - bp->b_bufsize;
	if (diff < 0)
		atomic_subtract_long(&bufmallocspace, -diff);
	else
		atomic_add_long(&bufmallocspace, diff);
	bp->b_bufsize = bufsize;
}