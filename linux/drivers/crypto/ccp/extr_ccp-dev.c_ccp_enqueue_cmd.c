#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccp_device {unsigned int cmd_q_count; scalar_t__ cmd_count; TYPE_1__* cmd_q; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  suspending; int /*<<< orphan*/  cmd; int /*<<< orphan*/  backlog; } ;
struct ccp_cmd {int flags; int /*<<< orphan*/  entry; struct ccp_device* ccp; int /*<<< orphan*/  callback; } ;
struct TYPE_2__ {int /*<<< orphan*/  kthread; scalar_t__ active; } ;

/* Variables and functions */
 int CCP_CMD_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOSPC ; 
 scalar_t__ MAX_CMD_QLEN ; 
 struct ccp_device* ccp_get_device () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

int ccp_enqueue_cmd(struct ccp_cmd *cmd)
{
	struct ccp_device *ccp;
	unsigned long flags;
	unsigned int i;
	int ret;

	/* Some commands might need to be sent to a specific device */
	ccp = cmd->ccp ? cmd->ccp : ccp_get_device();

	if (!ccp)
		return -ENODEV;

	/* Caller must supply a callback routine */
	if (!cmd->callback)
		return -EINVAL;

	cmd->ccp = ccp;

	spin_lock_irqsave(&ccp->cmd_lock, flags);

	i = ccp->cmd_q_count;

	if (ccp->cmd_count >= MAX_CMD_QLEN) {
		if (cmd->flags & CCP_CMD_MAY_BACKLOG) {
			ret = -EBUSY;
			list_add_tail(&cmd->entry, &ccp->backlog);
		} else {
			ret = -ENOSPC;
		}
	} else {
		ret = -EINPROGRESS;
		ccp->cmd_count++;
		list_add_tail(&cmd->entry, &ccp->cmd);

		/* Find an idle queue */
		if (!ccp->suspending) {
			for (i = 0; i < ccp->cmd_q_count; i++) {
				if (ccp->cmd_q[i].active)
					continue;

				break;
			}
		}
	}

	spin_unlock_irqrestore(&ccp->cmd_lock, flags);

	/* If we found an idle queue, wake it up */
	if (i < ccp->cmd_q_count)
		wake_up_process(ccp->cmd_q[i].kthread);

	return ret;
}