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
struct mlx5_core_dev {int dummy; } ;
struct mlx5_cmd_work_ent {int ret; unsigned long idx; int /*<<< orphan*/  status; int /*<<< orphan*/  in; int /*<<< orphan*/  done; scalar_t__ polling; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MLX5_CMD_MODE_EVENTS ; 
 int /*<<< orphan*/  MLX5_CMD_TIMEOUT_MSEC ; 
 int /*<<< orphan*/  deliv_status_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cmd_comp_handler (struct mlx5_core_dev*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_command_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_to_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wait_func(struct mlx5_core_dev *dev, struct mlx5_cmd_work_ent *ent)
{
	int timeout = msecs_to_jiffies(MLX5_CMD_TIMEOUT_MSEC);
	int err;

	if (ent->polling) {
		wait_for_completion(&ent->done);
	} else if (!wait_for_completion_timeout(&ent->done, timeout)) {
                ent->ret = -ETIMEDOUT;
                mlx5_cmd_comp_handler(dev, 1UL << ent->idx, MLX5_CMD_MODE_EVENTS);
        }

        err = ent->ret;

	if (err == -ETIMEDOUT) {
		mlx5_core_warn(dev, "%s(0x%x) timeout. Will cause a leak of a command resource\n",
			       mlx5_command_str(msg_to_opcode(ent->in)),
			       msg_to_opcode(ent->in));
	}
	mlx5_core_dbg(dev, "err %d, delivery status %s(%d)\n",
		      err, deliv_status_to_str(ent->status), ent->status);

	return err;
}