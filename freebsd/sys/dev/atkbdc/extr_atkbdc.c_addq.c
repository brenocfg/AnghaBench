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
struct TYPE_3__ {size_t tail; size_t head; int* q; scalar_t__ qcount; scalar_t__ max_qcount; int /*<<< orphan*/  call_count; } ;
typedef  TYPE_1__ kqueue ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 size_t nextq (size_t) ; 

__attribute__((used)) static int
addq(kqueue *q, int c)
{
    if (nextq(q->tail) != q->head) {
	q->q[q->tail] = c;
	q->tail = nextq(q->tail);
#if KBDIO_DEBUG >= 2
        ++q->call_count;
        ++q->qcount;
	if (q->qcount > q->max_qcount)
            q->max_qcount = q->qcount;
#endif
	return TRUE;
    }
    return FALSE;
}