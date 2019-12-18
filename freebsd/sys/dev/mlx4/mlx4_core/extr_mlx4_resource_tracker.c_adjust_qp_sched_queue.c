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
typedef  int u8 ;
struct TYPE_4__ {int sched_queue; } ;
struct TYPE_3__ {int sched_queue; } ;
struct mlx4_qp_context {TYPE_2__ alt_path; TYPE_1__ pri_path; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {scalar_t__ buf; } ;
typedef  enum mlx4_qp_optpar { ____Placeholder_mlx4_qp_optpar } mlx4_qp_optpar ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_QP_OPTPAR_ALT_ADDR_PATH ; 
 int MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH ; 
 int MLX4_QP_OPTPAR_SCHED_QUEUE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_eth (struct mlx4_dev*,int) ; 
 int mlx4_slave_convert_port (struct mlx4_dev*,int,int) ; 

__attribute__((used)) static int adjust_qp_sched_queue(struct mlx4_dev *dev, int slave,
				  struct mlx4_qp_context *qpc,
				  struct mlx4_cmd_mailbox *inbox)
{
	enum mlx4_qp_optpar optpar = be32_to_cpu(*(__be32 *)inbox->buf);
	u8 pri_sched_queue;
	int port = mlx4_slave_convert_port(
		   dev, slave, (qpc->pri_path.sched_queue >> 6 & 1) + 1) - 1;

	if (port < 0)
		return -EINVAL;

	pri_sched_queue = (qpc->pri_path.sched_queue & ~(1 << 6)) |
			  ((port & 1) << 6);

	if (optpar & (MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH | MLX4_QP_OPTPAR_SCHED_QUEUE) ||
	    qpc->pri_path.sched_queue || mlx4_is_eth(dev, port + 1)) {
		qpc->pri_path.sched_queue = pri_sched_queue;
	}

	if (optpar & MLX4_QP_OPTPAR_ALT_ADDR_PATH) {
		port = mlx4_slave_convert_port(
				dev, slave, (qpc->alt_path.sched_queue >> 6 & 1)
				+ 1) - 1;
		if (port < 0)
			return -EINVAL;
		qpc->alt_path.sched_queue =
			(qpc->alt_path.sched_queue & ~(1 << 6)) |
			(port & 1) << 6;
	}
	return 0;
}