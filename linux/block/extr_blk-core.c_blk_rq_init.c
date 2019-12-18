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
struct request {int tag; int internal_tag; int /*<<< orphan*/  ref; int /*<<< orphan*/ * part; int /*<<< orphan*/  start_time_ns; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  hash; scalar_t__ __sector; struct request_queue* q; int /*<<< orphan*/  queuelist; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  memset (struct request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

void blk_rq_init(struct request_queue *q, struct request *rq)
{
	memset(rq, 0, sizeof(*rq));

	INIT_LIST_HEAD(&rq->queuelist);
	rq->q = q;
	rq->__sector = (sector_t) -1;
	INIT_HLIST_NODE(&rq->hash);
	RB_CLEAR_NODE(&rq->rb_node);
	rq->tag = -1;
	rq->internal_tag = -1;
	rq->start_time_ns = ktime_get_ns();
	rq->part = NULL;
	refcount_set(&rq->ref, 1);
}