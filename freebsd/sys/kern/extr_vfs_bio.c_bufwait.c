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
struct buf {scalar_t__ b_iocmd; int b_flags; int b_ioflags; int b_error; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 scalar_t__ BIO_READ ; 
 int B_EINTR ; 
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bwait (struct buf*,int /*<<< orphan*/ ,char*) ; 

int
bufwait(struct buf *bp)
{
	if (bp->b_iocmd == BIO_READ)
		bwait(bp, PRIBIO, "biord");
	else
		bwait(bp, PRIBIO, "biowr");
	if (bp->b_flags & B_EINTR) {
		bp->b_flags &= ~B_EINTR;
		return (EINTR);
	}
	if (bp->b_ioflags & BIO_ERROR) {
		return (bp->b_error ? bp->b_error : EIO);
	} else {
		return (0);
	}
}