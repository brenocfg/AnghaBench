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
typedef  int u64 ;
typedef  unsigned int u32 ;
struct mlx5_cmd {int* ent_mode; int /*<<< orphan*/  checksum_disabled; struct mlx5_cmd_work_ent** ent_arr; TYPE_3__* cmd_page; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;
struct mlx5_cmd_work_ent {int status; int /*<<< orphan*/  idx; scalar_t__ ret; TYPE_2__* lay; TYPE_3__* out; int /*<<< orphan*/  ts2; int /*<<< orphan*/  cb_timeout_work; scalar_t__ callback; } ;
typedef  enum mlx5_cmd_mode { ____Placeholder_mlx5_cmd_mode } mlx5_cmd_mode ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ first; } ;
struct TYPE_5__ {int status_own; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int MLX5_DRIVER_STATUS_ABORTED ; 
 int MLX5_TRIGGERED_CMD_COMP ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_command (struct mlx5_cmd_work_ent*) ; 
 int /*<<< orphan*/  deliv_status_to_str (int) ; 
 int /*<<< orphan*/  dump_command (struct mlx5_core_dev*,struct mlx5_cmd_work_ent*,int /*<<< orphan*/ ) ; 
 int ffs (unsigned int) ; 
 int /*<<< orphan*/  free_ent (struct mlx5_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fwp_invalidate (TYPE_3__*) ; 
 scalar_t__ verify_signature (struct mlx5_cmd_work_ent*) ; 

void mlx5_cmd_comp_handler(struct mlx5_core_dev *dev, u64 vector_flags,
    enum mlx5_cmd_mode cmd_mode)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	struct mlx5_cmd_work_ent *ent;
	bool triggered = (vector_flags & MLX5_TRIGGERED_CMD_COMP) ? 1 : 0;
	u32 vector = vector_flags; /* discard flags in the upper dword */
	int i;

	/* make sure data gets read from RAM */
	mlx5_fwp_invalidate(cmd->cmd_page);

	while (vector != 0) {
		i = ffs(vector) - 1;
		vector &= ~(1U << i);
		/* check command mode */
		if (cmd->ent_mode[i] != cmd_mode)
			continue;
		ent = cmd->ent_arr[i];
		/* check if command was already handled */
		if (ent == NULL)
			continue;
                if (ent->callback)
                        cancel_delayed_work(&ent->cb_timeout_work);
		ent->ts2 = ktime_get_ns();
		memcpy(ent->out->first.data, ent->lay->out,
		       sizeof(ent->lay->out));
		/* make sure data gets read from RAM */
		mlx5_fwp_invalidate(ent->out);
		dump_command(dev, ent, 0);
		if (!ent->ret) {
			if (!cmd->checksum_disabled)
				ent->ret = verify_signature(ent);
			else
				ent->ret = 0;

			if (triggered)
				ent->status = MLX5_DRIVER_STATUS_ABORTED;
			else
				ent->status = ent->lay->status_own >> 1;

			mlx5_core_dbg(dev,
				      "FW command ret 0x%x, status %s(0x%x)\n",
				      ent->ret,
				      deliv_status_to_str(ent->status),
				      ent->status);
		}
		free_ent(cmd, ent->idx);
		complete_command(ent);
	}
}