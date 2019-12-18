#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int use_events; int max_cmds; int token_mask; int /*<<< orphan*/  switch_sem; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  event_sem; scalar_t__ free_head; TYPE_2__* context; } ;
struct mlx4_priv {TYPE_1__ cmd; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_context {int dummy; } ;
struct TYPE_4__ {int token; int next; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int mlx4_cmd_use_events(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i;

	if (priv->cmd.use_events != 0)
		return 0;

	priv->cmd.context = kmalloc(priv->cmd.max_cmds *
				   sizeof (struct mlx4_cmd_context),
				   GFP_KERNEL);
	if (!priv->cmd.context)
		return -ENOMEM;

	down_write(&priv->cmd.switch_sem);
	for (i = 0; i < priv->cmd.max_cmds; ++i) {
		priv->cmd.context[i].token = i;
		priv->cmd.context[i].next  = i + 1;
		/* To support fatal error flow, initialize all
		 * cmd contexts to allow simulating completions
		 * with complete() at any time.
		 */
		init_completion(&priv->cmd.context[i].done);
	}

	priv->cmd.context[priv->cmd.max_cmds - 1].next = -1;
	priv->cmd.free_head = 0;

	for (i = 0; i != priv->cmd.max_cmds; i++)
		up(&priv->cmd.event_sem);

	for (priv->cmd.token_mask = 1;
	     priv->cmd.token_mask < priv->cmd.max_cmds;
	     priv->cmd.token_mask <<= 1)
		; /* nothing */
	--priv->cmd.token_mask;

	down(&priv->cmd.poll_sem);
	priv->cmd.use_events = 1;
	up_write(&priv->cmd.switch_sem);

	return 0;
}