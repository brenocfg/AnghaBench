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
struct TYPE_4__ {int num_qps; int reserved_qps; int flags; int num_mgms; int num_amgms; scalar_t__ num_mpts; int /*<<< orphan*/  pkey_table_len; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wqes; scalar_t__ reserved_srqs; scalar_t__ num_srqs; int /*<<< orphan*/  max_qp_init_rdma; scalar_t__ reserved_pds; scalar_t__ num_pds; scalar_t__ reserved_mrws; int /*<<< orphan*/  max_cqes; scalar_t__ reserved_cqs; scalar_t__ num_cqs; int /*<<< orphan*/  max_sg; int /*<<< orphan*/  max_wqes; int /*<<< orphan*/  page_size_cap; } ;
struct TYPE_3__ {int rdb_shift; } ;
struct mthca_dev {int mthca_flags; TYPE_2__ limits; TYPE_1__ qp_table; int /*<<< orphan*/  device_cap_flags; int /*<<< orphan*/  fw_ver; } ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_smp {scalar_t__ data; int /*<<< orphan*/  attr_id; } ;
struct ib_device_attr {int vendor_id; int hw_ver; unsigned long long max_mr_size; int max_qp; int max_qp_rd_atom; int max_res_rd_atom; int max_mcast_grp; int max_mcast_qp_attach; int max_total_mcast_qp_attach; int max_map_per_fmr; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; scalar_t__ max_srq; int /*<<< orphan*/  max_qp_init_rd_atom; scalar_t__ max_pd; scalar_t__ max_mr; int /*<<< orphan*/  max_cqe; scalar_t__ max_cq; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  device_cap_flags; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int DEV_LIM_FLAG_ATOMIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ATOMIC_HCA ; 
 int /*<<< orphan*/  IB_ATOMIC_NONE ; 
 int /*<<< orphan*/  IB_SMP_ATTR_NODE_INFO ; 
 int MTHCA_FLAG_SINAI_OPT ; 
 int MTHCA_QP_PER_MGM ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  init_query_mad (struct ib_smp*) ; 
 int /*<<< orphan*/  kfree (struct ib_smp*) ; 
 struct ib_smp* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ib_smp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct ib_device_attr*,int /*<<< orphan*/ ,int) ; 
 int mthca_MAD_IFC (struct mthca_dev*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ib_smp*,struct ib_smp*) ; 
 struct mthca_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mthca_query_device(struct ib_device *ibdev, struct ib_device_attr *props,
			      struct ib_udata *uhw)
{
	struct ib_smp *in_mad  = NULL;
	struct ib_smp *out_mad = NULL;
	int err = -ENOMEM;
	struct mthca_dev *mdev = to_mdev(ibdev);

	if (uhw->inlen || uhw->outlen)
		return -EINVAL;

	in_mad  = kzalloc(sizeof *in_mad, GFP_KERNEL);
	out_mad = kmalloc(sizeof *out_mad, GFP_KERNEL);
	if (!in_mad || !out_mad)
		goto out;

	memset(props, 0, sizeof *props);

	props->fw_ver              = mdev->fw_ver;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mthca_MAD_IFC(mdev, 1, 1,
			    1, NULL, NULL, in_mad, out_mad);
	if (err)
		goto out;

	props->device_cap_flags    = mdev->device_cap_flags;
	props->vendor_id           = be32_to_cpup((__be32 *) (out_mad->data + 36)) &
		0xffffff;
	props->vendor_part_id      = be16_to_cpup((__be16 *) (out_mad->data + 30));
	props->hw_ver              = be32_to_cpup((__be32 *) (out_mad->data + 32));
	memcpy(&props->sys_image_guid, out_mad->data +  4, 8);

	props->max_mr_size         = ~0ull;
	props->page_size_cap       = mdev->limits.page_size_cap;
	props->max_qp              = mdev->limits.num_qps - mdev->limits.reserved_qps;
	props->max_qp_wr           = mdev->limits.max_wqes;
	props->max_sge             = mdev->limits.max_sg;
	props->max_sge_rd          = props->max_sge;
	props->max_cq              = mdev->limits.num_cqs - mdev->limits.reserved_cqs;
	props->max_cqe             = mdev->limits.max_cqes;
	props->max_mr              = mdev->limits.num_mpts - mdev->limits.reserved_mrws;
	props->max_pd              = mdev->limits.num_pds - mdev->limits.reserved_pds;
	props->max_qp_rd_atom      = 1 << mdev->qp_table.rdb_shift;
	props->max_qp_init_rd_atom = mdev->limits.max_qp_init_rdma;
	props->max_res_rd_atom     = props->max_qp_rd_atom * props->max_qp;
	props->max_srq             = mdev->limits.num_srqs - mdev->limits.reserved_srqs;
	props->max_srq_wr          = mdev->limits.max_srq_wqes;
	props->max_srq_sge         = mdev->limits.max_srq_sge;
	props->local_ca_ack_delay  = mdev->limits.local_ca_ack_delay;
	props->atomic_cap          = mdev->limits.flags & DEV_LIM_FLAG_ATOMIC ?
					IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->max_pkeys           = mdev->limits.pkey_table_len;
	props->max_mcast_grp       = mdev->limits.num_mgms + mdev->limits.num_amgms;
	props->max_mcast_qp_attach = MTHCA_QP_PER_MGM;
	props->max_total_mcast_qp_attach = props->max_mcast_qp_attach *
					   props->max_mcast_grp;
	/*
	 * If Sinai memory key optimization is being used, then only
	 * the 8-bit key portion will change.  For other HCAs, the
	 * unused index bits will also be used for FMR remapping.
	 */
	if (mdev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		props->max_map_per_fmr = 255;
	else
		props->max_map_per_fmr =
			(1 << (32 - ilog2(mdev->limits.num_mpts))) - 1;

	err = 0;
 out:
	kfree(in_mad);
	kfree(out_mad);
	return err;
}