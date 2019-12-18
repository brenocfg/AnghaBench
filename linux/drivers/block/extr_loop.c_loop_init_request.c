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
struct request {int dummy; } ;
struct loop_cmd {int /*<<< orphan*/  work; } ;
struct blk_mq_tag_set {int dummy; } ;

/* Variables and functions */
 struct loop_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_queue_work ; 

__attribute__((used)) static int loop_init_request(struct blk_mq_tag_set *set, struct request *rq,
		unsigned int hctx_idx, unsigned int numa_node)
{
	struct loop_cmd *cmd = blk_mq_rq_to_pdu(rq);

	kthread_init_work(&cmd->work, loop_queue_work);
	return 0;
}