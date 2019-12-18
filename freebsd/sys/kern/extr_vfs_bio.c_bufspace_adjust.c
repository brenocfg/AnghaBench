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
struct bufdomain {long bd_bufspacethresh; int /*<<< orphan*/  bd_bufspace; } ;
struct buf {int b_flags; int b_bufsize; } ;

/* Variables and functions */
 int B_MALLOC ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 long atomic_fetchadd_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,int) ; 
 struct bufdomain* bufdomain (struct buf*) ; 
 int /*<<< orphan*/  bufspace_daemon_wakeup (struct bufdomain*) ; 

__attribute__((used)) static void
bufspace_adjust(struct buf *bp, int bufsize)
{
	struct bufdomain *bd;
	long space;
	int diff;

	KASSERT((bp->b_flags & B_MALLOC) == 0,
	    ("bufspace_adjust: malloc buf %p", bp));
	bd = bufdomain(bp);
	diff = bufsize - bp->b_bufsize;
	if (diff < 0) {
		atomic_subtract_long(&bd->bd_bufspace, -diff);
	} else if (diff > 0) {
		space = atomic_fetchadd_long(&bd->bd_bufspace, diff);
		/* Wake up the daemon on the transition. */
		if (space < bd->bd_bufspacethresh &&
		    space + diff >= bd->bd_bufspacethresh)
			bufspace_daemon_wakeup(bd);
	}
	bp->b_bufsize = bufsize;
}