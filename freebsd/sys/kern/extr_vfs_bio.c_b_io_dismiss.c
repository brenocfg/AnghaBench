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
struct buf {int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_dep; int /*<<< orphan*/  b_xflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BX_ALTDATA ; 
 int /*<<< orphan*/  B_DIRECT ; 
 int /*<<< orphan*/  B_NOREUSE ; 
 int /*<<< orphan*/  B_RELBUF ; 
 int IO_DIRECT ; 
 int IO_EXT ; 
 int IO_NOREUSE ; 
 int IO_VMIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bqrelse (struct buf*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 

__attribute__((used)) static void
b_io_dismiss(struct buf *bp, int ioflag, bool release)
{

	KASSERT((ioflag & IO_NOREUSE) == 0 || (ioflag & IO_VMIO) != 0,
	    ("buf %p non-VMIO noreuse", bp));

	if ((ioflag & IO_DIRECT) != 0)
		bp->b_flags |= B_DIRECT;
	if ((ioflag & IO_EXT) != 0)
		bp->b_xflags |= BX_ALTDATA;
	if ((ioflag & (IO_VMIO | IO_DIRECT)) != 0 && LIST_EMPTY(&bp->b_dep)) {
		bp->b_flags |= B_RELBUF;
		if ((ioflag & IO_NOREUSE) != 0)
			bp->b_flags |= B_NOREUSE;
		if (release)
			brelse(bp);
	} else if (release)
		bqrelse(bp);
}