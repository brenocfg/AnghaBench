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
struct TYPE_3__ {int write; int read; int size; int /*<<< orphan*/  pop; int /*<<< orphan*/ ** storage; int /*<<< orphan*/  push; } ;
typedef  TYPE_1__ VCHIU_QUEUE_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

VCHIQ_HEADER_T *vchiu_queue_pop(VCHIU_QUEUE_T *queue)
{
	VCHIQ_HEADER_T *header;

	while (queue->write == queue->read) {
		if (down_interruptible(&queue->push) != 0) {
			flush_signals(current);
		}
	}

	/*
	 * Read from queue->storage must be visible after read from
	 * queue->write
	 */
	smp_rmb();

	header = queue->storage[queue->read & (queue->size - 1)];

	/*
	 * Read from queue->storage must be visible before write to
	 * queue->read
	 */
	smp_mb();

	queue->read++;

	up(&queue->pop);

	return header;
}