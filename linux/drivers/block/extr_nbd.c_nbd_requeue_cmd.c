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
struct nbd_cmd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_CMD_REQUEUED ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 struct request* blk_mq_rq_from_pdu (struct nbd_cmd*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_requeue_cmd(struct nbd_cmd *cmd)
{
	struct request *req = blk_mq_rq_from_pdu(cmd);

	if (!test_and_set_bit(NBD_CMD_REQUEUED, &cmd->flags))
		blk_mq_requeue_request(req, true);
}