#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* smp_queue_head; TYPE_2__* smp_queue_tail; } ;
typedef  TYPE_1__ smp_engine_t ;
struct TYPE_6__ {struct TYPE_6__* qnext; } ;
typedef  TYPE_2__ ibnd_smp_t ;

/* Variables and functions */

__attribute__((used)) static ibnd_smp_t *get_smp(smp_engine_t * engine)
{
	ibnd_smp_t *head = engine->smp_queue_head;
	ibnd_smp_t *tail = engine->smp_queue_tail;
	ibnd_smp_t *rc = head;
	if (head) {
		if (tail == head)
			engine->smp_queue_tail = NULL;
		engine->smp_queue_head = head->qnext;
	}
	return rc;
}