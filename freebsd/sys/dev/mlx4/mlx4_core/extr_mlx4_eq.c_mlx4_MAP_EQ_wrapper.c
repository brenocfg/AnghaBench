#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  long long u64 ;
typedef  int u32 ;
struct mlx4_vhcr {int in_modifier; long long in_param; } ;
struct mlx4_slave_event_eq_info {int eqn; } ;
struct TYPE_6__ {TYPE_1__* slave_state; } ;
struct TYPE_7__ {TYPE_2__ master; } ;
struct mlx4_priv {TYPE_3__ mfunc; } ;
struct TYPE_8__ {int function; } ;
struct mlx4_dev {TYPE_4__ caps; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_5__ {struct mlx4_slave_event_eq_info* event_eq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_MAP_EQ ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int MLX4_EVENT_TYPES_NUM ; 
 int mlx4_cmd (struct mlx4_dev*,long long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_MAP_EQ_wrapper(struct mlx4_dev *dev, int slave,
			struct mlx4_vhcr *vhcr,
			struct mlx4_cmd_mailbox *inbox,
			struct mlx4_cmd_mailbox *outbox,
			struct mlx4_cmd_info *cmd)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_slave_event_eq_info *event_eq =
		priv->mfunc.master.slave_state[slave].event_eq;
	u32 in_modifier = vhcr->in_modifier;
	u32 eqn = in_modifier & 0x3FF;
	u64 in_param =  vhcr->in_param;
	int err = 0;
	int i;

	if (slave == dev->caps.function)
		err = mlx4_cmd(dev, in_param, (in_modifier & 0x80000000) | eqn,
			       0, MLX4_CMD_MAP_EQ, MLX4_CMD_TIME_CLASS_B,
			       MLX4_CMD_NATIVE);
	if (!err)
		for (i = 0; i < MLX4_EVENT_TYPES_NUM; ++i)
			if (in_param & (1LL << i))
				event_eq[i].eqn = in_modifier >> 31 ? -1 : eqn;

	return err;
}