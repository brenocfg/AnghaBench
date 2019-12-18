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
struct rr_si {TYPE_1__* head; TYPE_1__* tail; } ;
struct TYPE_2__ {struct TYPE_2__* qnext; scalar_t__ status; } ;

/* Variables and functions */

__attribute__((used)) static inline void
rr_remove_head(struct rr_si *si)
{
	if (si->head == NULL)
		return; /* empty queue */
	si->head->status = 0;

	if (si->head == si->tail) {
		si->head = si->tail = NULL;
		return;
	}

	si->head = si->head->qnext;
	si->tail->qnext = si->head;
}