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
typedef  int /*<<< orphan*/  queue ;

/* Variables and functions */
 int /*<<< orphan*/  dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void append_queue(
	queue *q1,
	queue *q2
	) 
{
	while (!empty(q2))
		enqueue(q1, dequeue(q2));
	destroy_queue(q2);
}