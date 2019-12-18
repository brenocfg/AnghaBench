#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mlx5_qp_path {int dci_cfi_prio_sl; int ecn_dscp; int fl_free_ar; int grh_mlid; scalar_t__ mgid_index; int static_rate; int port; int ackto_lt; int /*<<< orphan*/  rgid; int /*<<< orphan*/  tclass_flowlabel; int /*<<< orphan*/  hop_limit; void* rlid; int /*<<< orphan*/  udp_sport; int /*<<< orphan*/  rmac; void* pkey_index; } ;
struct TYPE_13__ {int /*<<< orphan*/  sq; } ;
struct TYPE_12__ {scalar_t__ wqe_cnt; } ;
struct TYPE_11__ {scalar_t__ qp_type; } ;
struct mlx5_ib_qp {TYPE_6__ raw_packet_qp; TYPE_5__ sq; TYPE_4__ ibqp; } ;
struct mlx5_ib_dev {TYPE_7__* mdev; int /*<<< orphan*/  ib_dev; } ;
struct ib_qp_attr {int alt_timeout; int timeout; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  alt_pkey_index; } ;
struct TYPE_9__ {int /*<<< orphan*/  raw; } ;
struct TYPE_10__ {scalar_t__ sgid_index; int traffic_class; int flow_label; TYPE_2__ dgid; int /*<<< orphan*/  hop_limit; } ;
struct ib_ah_attr {int ah_flags; int sl; int src_path_bits; int /*<<< orphan*/  static_rate; TYPE_3__ grh; int /*<<< orphan*/  dlid; int /*<<< orphan*/  dmac; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;
struct TYPE_14__ {TYPE_1__* port_caps; } ;
struct TYPE_8__ {scalar_t__ gid_table_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 int IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int IB_LINK_LAYER_ETHERNET ; 
 scalar_t__ IB_QPT_RAW_PACKET ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_TIMEOUT ; 
 int MLX5_PATH_FLAG_FL ; 
 int MLX5_PATH_FLAG_FREE_AR ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int ib_rate_to_mlx5 (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx5_get_roce_gid_type (struct mlx5_ib_dev*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  mlx5_get_roce_udp_sport (struct mlx5_ib_dev*,int,scalar_t__) ; 
 int modify_raw_packet_eth_prio (TYPE_7__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 
 int rdma_port_get_link_layer (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mlx5_set_path(struct mlx5_ib_dev *dev, struct mlx5_ib_qp *qp,
			 const struct ib_ah_attr *ah,
			 struct mlx5_qp_path *path, u8 port, int attr_mask,
			 u32 path_flags, const struct ib_qp_attr *attr,
			 bool alt)
{
	enum rdma_link_layer ll = rdma_port_get_link_layer(&dev->ib_dev, port);
	int err;
	enum ib_gid_type gid_type;

	if (attr_mask & IB_QP_PKEY_INDEX)
		path->pkey_index = cpu_to_be16(alt ? attr->alt_pkey_index :
						     attr->pkey_index);

	if (ah->ah_flags & IB_AH_GRH) {
		if (ah->grh.sgid_index >=
		    dev->mdev->port_caps[port - 1].gid_table_len) {
			pr_err("sgid_index (%u) too large. max is %d\n",
			       ah->grh.sgid_index,
			       dev->mdev->port_caps[port - 1].gid_table_len);
			return -EINVAL;
		}
	}

	if (ll == IB_LINK_LAYER_ETHERNET) {
		if (!(ah->ah_flags & IB_AH_GRH))
			return -EINVAL;
		err = mlx5_get_roce_gid_type(dev, port, ah->grh.sgid_index,
					     &gid_type);
		if (err)
			return err;
		memcpy(path->rmac, ah->dmac, sizeof(ah->dmac));
		path->udp_sport = mlx5_get_roce_udp_sport(dev, port,
							  ah->grh.sgid_index);
		path->dci_cfi_prio_sl = (ah->sl & 0x7) << 4;
		if (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP)
			path->ecn_dscp = (ah->grh.traffic_class >> 2) & 0x3f;
	} else {
		path->fl_free_ar = (path_flags & MLX5_PATH_FLAG_FL) ? 0x80 : 0;
		path->fl_free_ar |=
			(path_flags & MLX5_PATH_FLAG_FREE_AR) ? 0x40 : 0;
		path->rlid = cpu_to_be16(ah->dlid);
		path->grh_mlid = ah->src_path_bits & 0x7f;
		if (ah->ah_flags & IB_AH_GRH)
			path->grh_mlid	|= 1 << 7;
		path->dci_cfi_prio_sl = ah->sl & 0xf;
	}

	if (ah->ah_flags & IB_AH_GRH) {
		path->mgid_index = ah->grh.sgid_index;
		path->hop_limit  = ah->grh.hop_limit;
		path->tclass_flowlabel =
			cpu_to_be32((ah->grh.traffic_class << 20) |
				    (ah->grh.flow_label));
		memcpy(path->rgid, ah->grh.dgid.raw, 16);
	}

	err = ib_rate_to_mlx5(dev, ah->static_rate);
	if (err < 0)
		return err;
	path->static_rate = err;
	path->port = port;

	if (attr_mask & IB_QP_TIMEOUT)
		path->ackto_lt = (alt ? attr->alt_timeout : attr->timeout) << 3;

	if ((qp->ibqp.qp_type == IB_QPT_RAW_PACKET) && qp->sq.wqe_cnt)
		return modify_raw_packet_eth_prio(dev->mdev,
						  &qp->raw_packet_qp.sq,
						  ah->sl & 0xf);

	return 0;
}