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
struct mthca_qp_path {int g_mylmc; int static_rate; int mgid_index; int /*<<< orphan*/  rgid; int /*<<< orphan*/  sl_tclass_flowlabel; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  rlid; int /*<<< orphan*/  port_pkey; } ;
struct TYPE_4__ {int num_ports; int gid_table_len; } ;
struct mthca_dev {TYPE_1__ limits; } ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {int sgid_index; int traffic_class; int flow_label; TYPE_2__ dgid; int /*<<< orphan*/  hop_limit; } ;
struct ib_ah_attr {int port_num; int sl; int src_path_bits; int ah_flags; TYPE_3__ grh; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  dlid; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_rate_to_ib (struct mthca_dev*,int,int) ; 

__attribute__((used)) static void to_ib_ah_attr(struct mthca_dev *dev, struct ib_ah_attr *ib_ah_attr,
				struct mthca_qp_path *path)
{
	memset(ib_ah_attr, 0, sizeof *ib_ah_attr);
	ib_ah_attr->port_num 	  = (be32_to_cpu(path->port_pkey) >> 24) & 0x3;

	if (ib_ah_attr->port_num == 0 || ib_ah_attr->port_num > dev->limits.num_ports)
		return;

	ib_ah_attr->dlid     	  = be16_to_cpu(path->rlid);
	ib_ah_attr->sl       	  = be32_to_cpu(path->sl_tclass_flowlabel) >> 28;
	ib_ah_attr->src_path_bits = path->g_mylmc & 0x7f;
	ib_ah_attr->static_rate   = mthca_rate_to_ib(dev,
						     path->static_rate & 0xf,
						     ib_ah_attr->port_num);
	ib_ah_attr->ah_flags      = (path->g_mylmc & (1 << 7)) ? IB_AH_GRH : 0;
	if (ib_ah_attr->ah_flags) {
		ib_ah_attr->grh.sgid_index = path->mgid_index & (dev->limits.gid_table_len - 1);
		ib_ah_attr->grh.hop_limit  = path->hop_limit;
		ib_ah_attr->grh.traffic_class =
			(be32_to_cpu(path->sl_tclass_flowlabel) >> 20) & 0xff;
		ib_ah_attr->grh.flow_label =
			be32_to_cpu(path->sl_tclass_flowlabel) & 0xfffff;
		memcpy(ib_ah_attr->grh.dgid.raw,
			path->rgid, sizeof ib_ah_attr->grh.dgid.raw);
	}
}