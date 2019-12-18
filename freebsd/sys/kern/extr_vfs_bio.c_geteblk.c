#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct buf {int /*<<< orphan*/  b_flags; } ;
struct TYPE_2__ {int td_pflags; } ;

/* Variables and functions */
 int BKVAMASK ; 
 int /*<<< orphan*/  B_INVAL ; 
 int GB_NOWAIT_BD ; 
 int TDP_BUFNEED ; 
 int /*<<< orphan*/  allocbuf (struct buf*,int) ; 
 int /*<<< orphan*/  bufdomain (struct buf*) ; 
 int /*<<< orphan*/  bufspace_release (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* curthread ; 
 struct buf* getnewbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

struct buf *
geteblk(int size, int flags)
{
	struct buf *bp;
	int maxsize;

	maxsize = (size + BKVAMASK) & ~BKVAMASK;
	while ((bp = getnewbuf(NULL, 0, 0, maxsize, flags)) == NULL) {
		if ((flags & GB_NOWAIT_BD) &&
		    (curthread->td_pflags & TDP_BUFNEED) != 0)
			return (NULL);
	}
	allocbuf(bp, size);
	bufspace_release(bufdomain(bp), maxsize);
	bp->b_flags |= B_INVAL;	/* b_dep cleared by getnewbuf() */
	return (bp);
}