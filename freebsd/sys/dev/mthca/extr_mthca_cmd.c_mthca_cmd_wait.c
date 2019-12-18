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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {size_t free_head; int /*<<< orphan*/  event_sem; int /*<<< orphan*/  context_lock; struct mthca_cmd_context* context; scalar_t__ token_mask; } ;
struct mthca_dev {TYPE_1__ cmd; } ;
struct mthca_cmd_context {size_t next; int result; int /*<<< orphan*/  out_param; scalar_t__ status; int /*<<< orphan*/  done; int /*<<< orphan*/  token; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mthca_cmd_post (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int mthca_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mthca_cmd_wait(struct mthca_dev *dev,
			  u64 in_param,
			  u64 *out_param,
			  int out_is_imm,
			  u32 in_modifier,
			  u8 op_modifier,
			  u16 op,
			  unsigned long timeout)
{
	int err = 0;
	struct mthca_cmd_context *context;

	down(&dev->cmd.event_sem);

	spin_lock(&dev->cmd.context_lock);
	BUG_ON(dev->cmd.free_head < 0);
	context = &dev->cmd.context[dev->cmd.free_head];
	context->token += dev->cmd.token_mask + 1;
	dev->cmd.free_head = context->next;
	spin_unlock(&dev->cmd.context_lock);

	init_completion(&context->done);

	err = mthca_cmd_post(dev, in_param,
			     out_param ? *out_param : 0,
			     in_modifier, op_modifier,
			     op, context->token, 1);
	if (err)
		goto out;

	if (!wait_for_completion_timeout(&context->done, timeout)) {
		err = -EBUSY;
		goto out;
	}

	err = context->result;
	if (err)
		goto out;

	if (context->status) {
		mthca_dbg(dev, "Command %02x completed with status %02x\n",
			  op, context->status);
		err = mthca_status_to_errno(context->status);
	}

	if (out_is_imm)
		*out_param = context->out_param;

out:
	spin_lock(&dev->cmd.context_lock);
	context->next = dev->cmd.free_head;
	dev->cmd.free_head = context - dev->cmd.context;
	spin_unlock(&dev->cmd.context_lock);

	up(&dev->cmd.event_sem);
	return err;
}