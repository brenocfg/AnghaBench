#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nullb_cmd {TYPE_3__* bio; int /*<<< orphan*/  error; int /*<<< orphan*/  rq; TYPE_2__* nq; } ;
struct TYPE_6__ {int /*<<< orphan*/  bi_status; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int queue_mode; } ;

/* Variables and functions */
#define  NULL_Q_BIO 129 
#define  NULL_Q_MQ 128 
 int /*<<< orphan*/  bio_endio (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_mq_end_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd (struct nullb_cmd*) ; 

__attribute__((used)) static void end_cmd(struct nullb_cmd *cmd)
{
	int queue_mode = cmd->nq->dev->queue_mode;

	switch (queue_mode)  {
	case NULL_Q_MQ:
		blk_mq_end_request(cmd->rq, cmd->error);
		return;
	case NULL_Q_BIO:
		cmd->bio->bi_status = cmd->error;
		bio_endio(cmd->bio);
		break;
	}

	free_cmd(cmd);
}