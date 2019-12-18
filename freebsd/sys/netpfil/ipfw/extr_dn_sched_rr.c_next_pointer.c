#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rr_si {TYPE_2__* tail; TYPE_1__* head; } ;
struct TYPE_4__ {struct TYPE_4__* qnext; } ;
struct TYPE_3__ {struct TYPE_3__* qnext; } ;

/* Variables and functions */

__attribute__((used)) static inline void
next_pointer(struct rr_si *si)
{
	if (si->head == NULL)
		return; /* empty queue */

	si->head = si->head->qnext;
	si->tail = si->tail->qnext;
}