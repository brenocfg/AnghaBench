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
struct buf {scalar_t__ b_rcred; scalar_t__ b_wcred; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 scalar_t__ NOCRED ; 
 int /*<<< orphan*/  crfree (scalar_t__) ; 

__attribute__((used)) static void
pbuf_dtor(void *mem, int size, void *arg)
{
	struct buf *bp = mem;

	if (bp->b_rcred != NOCRED) {
		crfree(bp->b_rcred);
		bp->b_rcred = NOCRED;
	}
	if (bp->b_wcred != NOCRED) {
		crfree(bp->b_wcred);
		bp->b_wcred = NOCRED;
	}

	BUF_UNLOCK(bp);
}