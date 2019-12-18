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
struct buf {scalar_t__ b_error; int /*<<< orphan*/ * b_iodone; scalar_t__ b_ioflags; scalar_t__ b_flags; scalar_t__ b_xflags; int /*<<< orphan*/  b_kvabase; int /*<<< orphan*/  b_data; scalar_t__ b_qindex; void* b_wcred; void* b_rcred; int /*<<< orphan*/ * b_bufobj; int /*<<< orphan*/ * b_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_LOCK (struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 void* NOCRED ; 

__attribute__((used)) static int
pbuf_ctor(void *mem, int size, void *arg, int flags)
{
	struct buf *bp = mem;

	bp->b_vp = NULL;
	bp->b_bufobj = NULL;

	/* copied from initpbuf() */
	bp->b_rcred = NOCRED;
	bp->b_wcred = NOCRED;
	bp->b_qindex = 0;       /* On no queue (QUEUE_NONE) */
	bp->b_data = bp->b_kvabase;
	bp->b_xflags = 0;
	bp->b_flags = 0;
	bp->b_ioflags = 0;
	bp->b_iodone = NULL;
	bp->b_error = 0;
	BUF_LOCK(bp, LK_EXCLUSIVE, NULL);

	return (0);
}