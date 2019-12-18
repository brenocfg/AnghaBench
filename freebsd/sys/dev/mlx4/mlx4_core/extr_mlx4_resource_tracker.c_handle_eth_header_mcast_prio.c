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
struct mlx4_net_trans_rule_hw_eth {int dummy; } ;
struct mlx4_net_trans_rule_hw_ctrl {int /*<<< orphan*/  prio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_mac; } ;
struct _rule_hw {scalar_t__ size; scalar_t__ id; scalar_t__ rsvd; TYPE_1__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DOMAIN_NIC ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_eth_header_mcast_prio(struct mlx4_net_trans_rule_hw_ctrl *ctrl,
					 struct _rule_hw *eth_header)
{
	if (is_multicast_ether_addr(eth_header->eth.dst_mac) ||
	    is_broadcast_ether_addr(eth_header->eth.dst_mac)) {
		struct mlx4_net_trans_rule_hw_eth *eth =
			(struct mlx4_net_trans_rule_hw_eth *)eth_header;
		struct _rule_hw *next_rule = (struct _rule_hw *)(eth + 1);
		bool last_rule = next_rule->size == 0 && next_rule->id == 0 &&
			next_rule->rsvd == 0;

		if (last_rule)
			ctrl->prio = cpu_to_be16(MLX4_DOMAIN_NIC);
	}
}