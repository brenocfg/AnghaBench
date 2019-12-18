#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int initialized; int /*<<< orphan*/ * storage; int /*<<< orphan*/  push; int /*<<< orphan*/  pop; scalar_t__ write; scalar_t__ read; } ;
typedef  TYPE_1__ VCHIU_QUEUE_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pow2 (int) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiu_queue_delete (TYPE_1__*) ; 

int vchiu_queue_init(VCHIU_QUEUE_T *queue, int size)
{
	WARN_ON(!is_pow2(size));

	queue->size = size;
	queue->read = 0;
	queue->write = 0;
	queue->initialized = 1;

	_sema_init(&queue->pop, 0);
	_sema_init(&queue->push, 0);

	queue->storage = kzalloc(size * sizeof(VCHIQ_HEADER_T *), GFP_KERNEL);
	if (queue->storage == NULL) {
		vchiu_queue_delete(queue);
		return 0;
	}
	return 1;
}