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
typedef  int u8 ;
struct mlx4_net_trans_rule_hw_ctrl {int flags; int /*<<< orphan*/  qpn; int /*<<< orphan*/  port; int /*<<< orphan*/  prio; int /*<<< orphan*/  type; } ;
struct mlx4_net_trans_rule {scalar_t__ queue_mode; size_t promisc_mode; int /*<<< orphan*/  qpn; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; scalar_t__ allow_loopback; scalar_t__ exclusive; } ;

/* Variables and functions */
 scalar_t__ MLX4_NET_TRANS_Q_LIFO ; 
 int /*<<< orphan*/ * __promisc_mode ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trans_rule_ctrl_to_hw(struct mlx4_net_trans_rule *ctrl,
				  struct mlx4_net_trans_rule_hw_ctrl *hw)
{
	u8 flags = 0;

	flags = ctrl->queue_mode == MLX4_NET_TRANS_Q_LIFO ? 1 : 0;
	flags |= ctrl->exclusive ? (1 << 2) : 0;
	flags |= ctrl->allow_loopback ? (1 << 3) : 0;

	hw->flags = flags;
	hw->type = __promisc_mode[ctrl->promisc_mode];
	hw->prio = cpu_to_be16(ctrl->priority);
	hw->port = ctrl->port;
	hw->qpn = cpu_to_be32(ctrl->qpn);
}