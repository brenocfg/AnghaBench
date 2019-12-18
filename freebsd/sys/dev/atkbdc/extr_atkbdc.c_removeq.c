#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t tail; size_t head; int* q; int /*<<< orphan*/  qcount; } ;
typedef  TYPE_1__ kqueue ;

/* Variables and functions */
 size_t nextq (size_t) ; 

__attribute__((used)) static int
removeq(kqueue *q)
{
    int c;

    if (q->tail != q->head) {
	c = q->q[q->head];
	q->head = nextq(q->head);
#if KBDIO_DEBUG >= 2
        --q->qcount;
#endif
	return c;
    }
    return -1;
}