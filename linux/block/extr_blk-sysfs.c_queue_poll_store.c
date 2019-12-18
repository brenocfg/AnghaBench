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
struct request_queue {TYPE_2__* tag_set; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {size_t nr_maps; TYPE_1__* map; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_queues; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 size_t HCTX_TYPE_POLL ; 
 int /*<<< orphan*/  QUEUE_FLAG_POLL ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ queue_var_store (unsigned long*,char const*,size_t) ; 

__attribute__((used)) static ssize_t queue_poll_store(struct request_queue *q, const char *page,
				size_t count)
{
	unsigned long poll_on;
	ssize_t ret;

	if (!q->tag_set || q->tag_set->nr_maps <= HCTX_TYPE_POLL ||
	    !q->tag_set->map[HCTX_TYPE_POLL].nr_queues)
		return -EINVAL;

	ret = queue_var_store(&poll_on, page, count);
	if (ret < 0)
		return ret;

	if (poll_on)
		blk_queue_flag_set(QUEUE_FLAG_POLL, q);
	else
		blk_queue_flag_clear(QUEUE_FLAG_POLL, q);

	return ret;
}