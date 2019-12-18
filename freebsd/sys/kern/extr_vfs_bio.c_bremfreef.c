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
struct bufqueue {int dummy; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  bq_remove (struct bufqueue*,struct buf*) ; 
 struct bufqueue* bufqueue_acquire (struct buf*) ; 

void
bremfreef(struct buf *bp)
{
	struct bufqueue *bq;

	bq = bufqueue_acquire(bp);
	bq_remove(bq, bp);
	BQ_UNLOCK(bq);
}