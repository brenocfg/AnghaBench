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
struct work_struct {int dummy; } ;
struct request {int dummy; } ;
struct blk_mq_tag_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (struct work_struct*,int /*<<< orphan*/ ) ; 
 struct work_struct* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  rbd_queue_workfn ; 

__attribute__((used)) static int rbd_init_request(struct blk_mq_tag_set *set, struct request *rq,
		unsigned int hctx_idx, unsigned int numa_node)
{
	struct work_struct *work = blk_mq_rq_to_pdu(rq);

	INIT_WORK(work, rbd_queue_workfn);
	return 0;
}