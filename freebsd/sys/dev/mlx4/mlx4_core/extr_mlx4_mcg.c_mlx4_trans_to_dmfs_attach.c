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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  dst_gid_msk; int /*<<< orphan*/  dst_gid; } ;
struct TYPE_5__ {int /*<<< orphan*/  dst_mac_msk; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_4__ {int /*<<< orphan*/ * member_0; } ;
struct mlx4_spec_list {int /*<<< orphan*/  list; TYPE_3__ ib; int /*<<< orphan*/  id; TYPE_2__ eth; TYPE_1__ member_0; } ;
struct mlx4_qp {int /*<<< orphan*/  qpn; } ;
struct mlx4_net_trans_rule {int allow_loopback; int /*<<< orphan*/  list; int /*<<< orphan*/  qpn; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; int /*<<< orphan*/  promisc_mode; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  queue_mode; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX4_DOMAIN_NIC ; 
 int /*<<< orphan*/  MLX4_FS_REGULAR ; 
 int MLX4_MAC_MASK ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_Q_FIFO ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_RULE_ID_ETH ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_RULE_ID_IB ; 
#define  MLX4_PROT_ETH 129 
#define  MLX4_PROT_IB_IPV6 128 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int mlx4_flow_attach (struct mlx4_dev*,struct mlx4_net_trans_rule*,int /*<<< orphan*/ *) ; 

int mlx4_trans_to_dmfs_attach(struct mlx4_dev *dev, struct mlx4_qp *qp,
			      u8 gid[16], u8 port,
			      int block_mcast_loopback,
			      enum mlx4_protocol prot, u64 *reg_id)
{
		struct mlx4_spec_list spec = { {NULL} };
		__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

		struct mlx4_net_trans_rule rule = {
			.queue_mode = MLX4_NET_TRANS_Q_FIFO,
			.exclusive = 0,
			.promisc_mode = MLX4_FS_REGULAR,
			.priority = MLX4_DOMAIN_NIC,
		};

		rule.allow_loopback = !block_mcast_loopback;
		rule.port = port;
		rule.qpn = qp->qpn;
		INIT_LIST_HEAD(&rule.list);

		switch (prot) {
		case MLX4_PROT_ETH:
			spec.id = MLX4_NET_TRANS_RULE_ID_ETH;
			memcpy(spec.eth.dst_mac, &gid[10], ETH_ALEN);
			memcpy(spec.eth.dst_mac_msk, &mac_mask, ETH_ALEN);
			break;

		case MLX4_PROT_IB_IPV6:
			spec.id = MLX4_NET_TRANS_RULE_ID_IB;
			memcpy(spec.ib.dst_gid, gid, 16);
			memset(&spec.ib.dst_gid_msk, 0xff, 16);
			break;
		default:
			return -EINVAL;
		}
		list_add_tail(&spec.list, &rule.list);

		return mlx4_flow_attach(dev, &rule, reg_id);
}