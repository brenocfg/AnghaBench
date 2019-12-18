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
struct request_queue {struct elevator_queue* elevator; } ;
struct request {int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  hash; } ;
struct elevator_queue {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELV_ON_HASH (struct request*) ; 
 int /*<<< orphan*/  RQF_HASHED ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_hash_key (struct request*) ; 

void elv_rqhash_add(struct request_queue *q, struct request *rq)
{
	struct elevator_queue *e = q->elevator;

	BUG_ON(ELV_ON_HASH(rq));
	hash_add(e->hash, &rq->hash, rq_hash_key(rq));
	rq->rq_flags |= RQF_HASHED;
}