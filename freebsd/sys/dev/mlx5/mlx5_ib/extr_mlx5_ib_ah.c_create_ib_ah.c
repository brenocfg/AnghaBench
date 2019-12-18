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
struct mlx5_ib_dev {int dummy; } ;
struct ib_ah {int dummy; } ;
struct TYPE_4__ {int stat_rate_sl; int fl_mlid; int /*<<< orphan*/  rlid; int /*<<< orphan*/  udp_sport; int /*<<< orphan*/  rmac; int /*<<< orphan*/  tclass; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  grh_gid_fl; int /*<<< orphan*/  rgid; } ;
struct mlx5_ib_ah {struct ib_ah ibah; TYPE_2__ av; } ;
struct TYPE_3__ {int flow_label; int sgid_index; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  dgid; } ;
struct ib_ah_attr {int ah_flags; int static_rate; int sl; int src_path_bits; int /*<<< orphan*/  dlid; TYPE_1__ grh; int /*<<< orphan*/  port_num; int /*<<< orphan*/ * dmac; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_get_roce_udp_sport (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ib_ah *create_ib_ah(struct mlx5_ib_dev *dev,
				  struct mlx5_ib_ah *ah,
				  struct ib_ah_attr *ah_attr,
				  enum rdma_link_layer ll)
{
	if (ah_attr->ah_flags & IB_AH_GRH) {
		memcpy(ah->av.rgid, &ah_attr->grh.dgid, 16);
		ah->av.grh_gid_fl = cpu_to_be32(ah_attr->grh.flow_label |
						(1 << 30) |
						ah_attr->grh.sgid_index << 20);
		ah->av.hop_limit = ah_attr->grh.hop_limit;
		ah->av.tclass = ah_attr->grh.traffic_class;
	}

	ah->av.stat_rate_sl = (ah_attr->static_rate << 4);

	if (ll == IB_LINK_LAYER_ETHERNET) {
		memcpy(ah->av.rmac, ah_attr->dmac, sizeof(ah_attr->dmac));
		ah->av.udp_sport =
			mlx5_get_roce_udp_sport(dev,
						ah_attr->port_num,
						ah_attr->grh.sgid_index);
		ah->av.stat_rate_sl |= (ah_attr->sl & 0x7) << 1;
	} else {
		ah->av.rlid = cpu_to_be16(ah_attr->dlid);
		ah->av.fl_mlid = ah_attr->src_path_bits & 0x7f;
		ah->av.stat_rate_sl |= (ah_attr->sl & 0xf);
	}

	return &ah->ibah;
}