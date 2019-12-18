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
struct gtaskqueue {int /*<<< orphan*/  tq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_FLAGS_BLOCKED ; 
 int /*<<< orphan*/  TQ_LOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct gtaskqueue*) ; 

void
gtaskqueue_block(struct gtaskqueue *queue)
{

	TQ_LOCK(queue);
	queue->tq_flags |= TQ_FLAGS_BLOCKED;
	TQ_UNLOCK(queue);
}