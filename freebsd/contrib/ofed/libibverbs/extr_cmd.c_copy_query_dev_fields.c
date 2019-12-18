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
typedef  int /*<<< orphan*/  uint64_t ;
struct ibv_query_device_resp {int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_map_per_fmr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_total_mcast_qp_attach; int /*<<< orphan*/  max_mcast_qp_attach; int /*<<< orphan*/  max_mcast_grp; int /*<<< orphan*/  max_raw_ethy_qp; int /*<<< orphan*/  max_raw_ipv6_qp; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_rdd; int /*<<< orphan*/  max_ee; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_ee_init_rd_atom; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_res_rd_atom; int /*<<< orphan*/  max_ee_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  device_cap_flags; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  node_guid; int /*<<< orphan*/  fw_ver; } ;
struct ibv_device_attr {int /*<<< orphan*/  phys_port_cnt; int /*<<< orphan*/  local_ca_ack_delay; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_map_per_fmr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_total_mcast_qp_attach; int /*<<< orphan*/  max_mcast_qp_attach; int /*<<< orphan*/  max_mcast_grp; int /*<<< orphan*/  max_raw_ethy_qp; int /*<<< orphan*/  max_raw_ipv6_qp; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_rdd; int /*<<< orphan*/  max_ee; int /*<<< orphan*/  atomic_cap; int /*<<< orphan*/  max_ee_init_rd_atom; int /*<<< orphan*/  max_qp_init_rd_atom; int /*<<< orphan*/  max_res_rd_atom; int /*<<< orphan*/  max_ee_rd_atom; int /*<<< orphan*/  max_qp_rd_atom; int /*<<< orphan*/  max_pd; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  device_cap_flags; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/  vendor_part_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  page_size_cap; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  node_guid; } ;

/* Variables and functions */

__attribute__((used)) static void copy_query_dev_fields(struct ibv_device_attr *device_attr,
				  struct ibv_query_device_resp *resp,
				  uint64_t *raw_fw_ver)
{
	*raw_fw_ver				= resp->fw_ver;
	device_attr->node_guid			= resp->node_guid;
	device_attr->sys_image_guid		= resp->sys_image_guid;
	device_attr->max_mr_size		= resp->max_mr_size;
	device_attr->page_size_cap		= resp->page_size_cap;
	device_attr->vendor_id			= resp->vendor_id;
	device_attr->vendor_part_id		= resp->vendor_part_id;
	device_attr->hw_ver			= resp->hw_ver;
	device_attr->max_qp			= resp->max_qp;
	device_attr->max_qp_wr			= resp->max_qp_wr;
	device_attr->device_cap_flags		= resp->device_cap_flags;
	device_attr->max_sge			= resp->max_sge;
	device_attr->max_sge_rd			= resp->max_sge_rd;
	device_attr->max_cq			= resp->max_cq;
	device_attr->max_cqe			= resp->max_cqe;
	device_attr->max_mr			= resp->max_mr;
	device_attr->max_pd			= resp->max_pd;
	device_attr->max_qp_rd_atom		= resp->max_qp_rd_atom;
	device_attr->max_ee_rd_atom		= resp->max_ee_rd_atom;
	device_attr->max_res_rd_atom		= resp->max_res_rd_atom;
	device_attr->max_qp_init_rd_atom	= resp->max_qp_init_rd_atom;
	device_attr->max_ee_init_rd_atom	= resp->max_ee_init_rd_atom;
	device_attr->atomic_cap			= resp->atomic_cap;
	device_attr->max_ee			= resp->max_ee;
	device_attr->max_rdd			= resp->max_rdd;
	device_attr->max_mw			= resp->max_mw;
	device_attr->max_raw_ipv6_qp		= resp->max_raw_ipv6_qp;
	device_attr->max_raw_ethy_qp		= resp->max_raw_ethy_qp;
	device_attr->max_mcast_grp		= resp->max_mcast_grp;
	device_attr->max_mcast_qp_attach	= resp->max_mcast_qp_attach;
	device_attr->max_total_mcast_qp_attach	= resp->max_total_mcast_qp_attach;
	device_attr->max_ah			= resp->max_ah;
	device_attr->max_fmr			= resp->max_fmr;
	device_attr->max_map_per_fmr		= resp->max_map_per_fmr;
	device_attr->max_srq			= resp->max_srq;
	device_attr->max_srq_wr			= resp->max_srq_wr;
	device_attr->max_srq_sge		= resp->max_srq_sge;
	device_attr->max_pkeys			= resp->max_pkeys;
	device_attr->local_ca_ack_delay		= resp->local_ca_ack_delay;
	device_attr->phys_port_cnt		= resp->phys_port_cnt;
}