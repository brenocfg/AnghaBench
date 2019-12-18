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
typedef  scalar_t__ u32 ;
struct ib_uverbs_query_device_resp {int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_map_per_fmr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_total_mcast_qp_attach; int /*<<< orphan*/  max_mcast_qp_attach; int /*<<< orphan*/  max_mcast_grp; int /*<<< orphan*/  max_raw_ethy_qp; int /*<<< orphan*/  max_raw_ipv6_qp; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_rdd; int /*<<< orphan*/  max_ee; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_ee_init_rd_atom; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_res_rd_atom; int /*<<< orphan*/  max_ee_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; scalar_t__ device_cap_flags; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_uverbs_file {int dummy; } ;
struct ib_device_attr {int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_map_per_fmr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_total_mcast_qp_attach; int /*<<< orphan*/  max_mcast_qp_attach; int /*<<< orphan*/  max_mcast_grp; int /*<<< orphan*/  max_raw_ethy_qp; int /*<<< orphan*/  max_raw_ipv6_qp; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_rdd; int /*<<< orphan*/  max_ee; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_ee_init_rd_atom; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_res_rd_atom; int /*<<< orphan*/  max_ee_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; scalar_t__ device_cap_flags; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  fw_ver; } ;
struct ib_device {int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  node_guid; } ;

/* Variables and functions */

__attribute__((used)) static void copy_query_dev_fields(struct ib_uverbs_file *file,
				  struct ib_device *ib_dev,
				  struct ib_uverbs_query_device_resp *resp,
				  struct ib_device_attr *attr)
{
	resp->fw_ver		= attr->fw_ver;
	resp->node_guid		= ib_dev->node_guid;
	resp->sys_image_guid	= attr->sys_image_guid;
	resp->max_mr_size	= attr->max_mr_size;
	resp->page_size_cap	= attr->page_size_cap;
	resp->vendor_id		= attr->vendor_id;
	resp->vendor_part_id	= attr->vendor_part_id;
	resp->hw_ver		= attr->hw_ver;
	resp->max_qp		= attr->max_qp;
	resp->max_qp_wr		= attr->max_qp_wr;
	resp->device_cap_flags	= (u32)(attr->device_cap_flags);
	resp->max_sge		= attr->max_sge;
	resp->max_sge_rd	= attr->max_sge_rd;
	resp->max_cq		= attr->max_cq;
	resp->max_cqe		= attr->max_cqe;
	resp->max_mr		= attr->max_mr;
	resp->max_pd		= attr->max_pd;
	resp->max_qp_rd_atom	= attr->max_qp_rd_atom;
	resp->max_ee_rd_atom	= attr->max_ee_rd_atom;
	resp->max_res_rd_atom	= attr->max_res_rd_atom;
	resp->max_qp_init_rd_atom	= attr->max_qp_init_rd_atom;
	resp->max_ee_init_rd_atom	= attr->max_ee_init_rd_atom;
	resp->atomic_cap		= attr->atomic_cap;
	resp->max_ee			= attr->max_ee;
	resp->max_rdd			= attr->max_rdd;
	resp->max_mw			= attr->max_mw;
	resp->max_raw_ipv6_qp		= attr->max_raw_ipv6_qp;
	resp->max_raw_ethy_qp		= attr->max_raw_ethy_qp;
	resp->max_mcast_grp		= attr->max_mcast_grp;
	resp->max_mcast_qp_attach	= attr->max_mcast_qp_attach;
	resp->max_total_mcast_qp_attach	= attr->max_total_mcast_qp_attach;
	resp->max_ah			= attr->max_ah;
	resp->max_fmr			= attr->max_fmr;
	resp->max_map_per_fmr		= attr->max_map_per_fmr;
	resp->max_srq			= attr->max_srq;
	resp->max_srq_wr		= attr->max_srq_wr;
	resp->max_srq_sge		= attr->max_srq_sge;
	resp->max_pkeys			= attr->max_pkeys;
	resp->local_ca_ack_delay	= attr->local_ca_ack_delay;
	resp->phys_port_cnt		= ib_dev->phys_port_cnt;
}