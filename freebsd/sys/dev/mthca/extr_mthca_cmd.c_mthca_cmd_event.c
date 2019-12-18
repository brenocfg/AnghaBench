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
typedef  size_t u16 ;
struct TYPE_2__ {size_t token_mask; struct mthca_cmd_context* context; } ;
struct mthca_dev {TYPE_1__ cmd; } ;
struct mthca_cmd_context {size_t token; int /*<<< orphan*/  done; int /*<<< orphan*/  out_param; int /*<<< orphan*/  status; scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void mthca_cmd_event(struct mthca_dev *dev,
		     u16 token,
		     u8  status,
		     u64 out_param)
{
	struct mthca_cmd_context *context =
		&dev->cmd.context[token & dev->cmd.token_mask];

	/* previously timed out command completing at long last */
	if (token != context->token)
		return;

	context->result    = 0;
	context->status    = status;
	context->out_param = out_param;

	complete(&context->done);
}