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
struct bufqueue {int dummy; } ;
struct buf {int b_qindex; size_t b_subqueue; } ;
struct TYPE_2__ {struct bufqueue* bd_subq; struct bufqueue bd_dirtyq; } ;

/* Variables and functions */
#define  QUEUE_CLEAN 132 
#define  QUEUE_DIRTY 131 
#define  QUEUE_EMPTY 130 
#define  QUEUE_NONE 129 
#define  QUEUE_SENTINEL 128 
 struct bufqueue bqempty ; 
 TYPE_1__* bufdomain (struct buf*) ; 
 int /*<<< orphan*/  panic (char*,struct buf*,int) ; 

__attribute__((used)) static struct bufqueue *
bufqueue(struct buf *bp)
{

	switch (bp->b_qindex) {
	case QUEUE_NONE:
		/* FALLTHROUGH */
	case QUEUE_SENTINEL:
		return (NULL);
	case QUEUE_EMPTY:
		return (&bqempty);
	case QUEUE_DIRTY:
		return (&bufdomain(bp)->bd_dirtyq);
	case QUEUE_CLEAN:
		return (&bufdomain(bp)->bd_subq[bp->b_subqueue]);
	default:
		break;
	}
	panic("bufqueue(%p): Unhandled type %d\n", bp, bp->b_qindex);
}