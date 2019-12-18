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
struct mthca_qp_path {int g_mylmc; scalar_t__ mgid_index; void* sl_tclass_flowlabel; int /*<<< orphan*/  rgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  rlid; } ;
struct TYPE_4__ {scalar_t__ gid_table_len; } ;
struct mthca_dev {TYPE_1__ limits; } ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {scalar_t__ sgid_index; int traffic_class; int flow_label; TYPE_2__ dgid; int /*<<< orphan*/  hop_limit; } ;
struct ib_ah_attr {int src_path_bits; int ah_flags; int sl; TYPE_3__ grh; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  dlid; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mthca_get_rate (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_path_set(struct mthca_dev *dev, const struct ib_ah_attr *ah,
			  struct mthca_qp_path *path, u8 port)
{
	path->g_mylmc     = ah->src_path_bits & 0x7f;
	path->rlid        = cpu_to_be16(ah->dlid);
	path->static_rate = mthca_get_rate(dev, ah->static_rate, port);

	if (ah->ah_flags & IB_AH_GRH) {
		if (ah->grh.sgid_index >= dev->limits.gid_table_len) {
			mthca_dbg(dev, "sgid_index (%u) too large. max is %d\n",
				  ah->grh.sgid_index, dev->limits.gid_table_len-1);
			return -1;
		}

		path->g_mylmc   |= 1 << 7;
		path->mgid_index = ah->grh.sgid_index;
		path->hop_limit  = ah->grh.hop_limit;
		path->sl_tclass_flowlabel =
			cpu_to_be32((ah->sl << 28)                |
				    (ah->grh.traffic_class << 20) |
				    (ah->grh.flow_label));
		memcpy(path->rgid, ah->grh.dgid.raw, 16);
	} else
		path->sl_tclass_flowlabel = cpu_to_be32(ah->sl << 28);

	return 0;
}