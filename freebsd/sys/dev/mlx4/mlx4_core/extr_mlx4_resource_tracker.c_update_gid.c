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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int sched_queue; int mgid_index; } ;
struct TYPE_3__ {int sched_queue; int mgid_index; } ;
struct mlx4_qp_context {TYPE_2__ alt_path; TYPE_1__ pri_path; int /*<<< orphan*/  flags; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {struct mlx4_qp_context* buf; } ;
typedef  enum mlx4_qp_optpar { ____Placeholder_mlx4_qp_optpar } mlx4_qp_optpar ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int MLX4_QP_OPTPAR_ALT_ADDR_PATH ; 
 int MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH ; 
 scalar_t__ MLX4_QP_ST_RC ; 
 scalar_t__ MLX4_QP_ST_UC ; 
 scalar_t__ MLX4_QP_ST_UD ; 
 scalar_t__ MLX4_QP_ST_XRC ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int mlx4_get_base_gid_ix (struct mlx4_dev*,int,int) ; 
 scalar_t__ mlx4_is_eth (struct mlx4_dev*,int) ; 

__attribute__((used)) static void update_gid(struct mlx4_dev *dev, struct mlx4_cmd_mailbox *inbox,
		       u8 slave)
{
	struct mlx4_qp_context	*qp_ctx = inbox->buf + 8;
	enum mlx4_qp_optpar	optpar = be32_to_cpu(*(__be32 *) inbox->buf);
	u32			ts = (be32_to_cpu(qp_ctx->flags) >> 16) & 0xff;
	int port;

	if (MLX4_QP_ST_UD == ts) {
		port = (qp_ctx->pri_path.sched_queue >> 6 & 1) + 1;
		if (mlx4_is_eth(dev, port))
			qp_ctx->pri_path.mgid_index =
				mlx4_get_base_gid_ix(dev, slave, port) | 0x80;
		else
			qp_ctx->pri_path.mgid_index = slave | 0x80;

	} else if (MLX4_QP_ST_RC == ts || MLX4_QP_ST_XRC == ts || MLX4_QP_ST_UC == ts) {
		if (optpar & MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH) {
			port = (qp_ctx->pri_path.sched_queue >> 6 & 1) + 1;
			if (mlx4_is_eth(dev, port)) {
				qp_ctx->pri_path.mgid_index +=
					mlx4_get_base_gid_ix(dev, slave, port);
				qp_ctx->pri_path.mgid_index &= 0x7f;
			} else {
				qp_ctx->pri_path.mgid_index = slave & 0x7F;
			}
		}
		if (optpar & MLX4_QP_OPTPAR_ALT_ADDR_PATH) {
			port = (qp_ctx->alt_path.sched_queue >> 6 & 1) + 1;
			if (mlx4_is_eth(dev, port)) {
				qp_ctx->alt_path.mgid_index +=
					mlx4_get_base_gid_ix(dev, slave, port);
				qp_ctx->alt_path.mgid_index &= 0x7f;
			} else {
				qp_ctx->alt_path.mgid_index = slave & 0x7F;
			}
		}
	}
}