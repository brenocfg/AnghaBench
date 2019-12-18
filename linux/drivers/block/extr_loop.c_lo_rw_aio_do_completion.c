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
struct loop_cmd {int /*<<< orphan*/ * bvec; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 struct request* blk_mq_rq_from_pdu (struct loop_cmd*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lo_rw_aio_do_completion(struct loop_cmd *cmd)
{
	struct request *rq = blk_mq_rq_from_pdu(cmd);

	if (!atomic_dec_and_test(&cmd->ref))
		return;
	kfree(cmd->bvec);
	cmd->bvec = NULL;
	blk_mq_complete_request(rq);
}