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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/ * biotail; int /*<<< orphan*/  bio; scalar_t__ __sector; scalar_t__ __data_len; } ;
struct blk_mq_alloc_data {unsigned int cmd_flags; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  blk_mq_req_flags_t ;

/* Variables and functions */
 struct request* ERR_PTR (int) ; 
 int EWOULDBLOCK ; 
 struct request* blk_mq_get_request (struct request_queue*,int /*<<< orphan*/ *,struct blk_mq_alloc_data*) ; 
 int blk_queue_enter (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_exit (struct request_queue*) ; 

struct request *blk_mq_alloc_request(struct request_queue *q, unsigned int op,
		blk_mq_req_flags_t flags)
{
	struct blk_mq_alloc_data alloc_data = { .flags = flags, .cmd_flags = op };
	struct request *rq;
	int ret;

	ret = blk_queue_enter(q, flags);
	if (ret)
		return ERR_PTR(ret);

	rq = blk_mq_get_request(q, NULL, &alloc_data);
	blk_queue_exit(q);

	if (!rq)
		return ERR_PTR(-EWOULDBLOCK);

	rq->__data_len = 0;
	rq->__sector = (sector_t) -1;
	rq->bio = rq->biotail = NULL;
	return rq;
}