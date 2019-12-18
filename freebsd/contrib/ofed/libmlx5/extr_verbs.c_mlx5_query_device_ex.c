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
typedef  int uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_hash_function; int /*<<< orphan*/  rx_hash_fields_mask; } ;
struct mlx5_query_device_ex_resp {int /*<<< orphan*/  cqe_comp_caps; scalar_t__ support_multi_pkt_send_wqe; TYPE_3__ packet_pacing_caps; TYPE_2__ rss_caps; int /*<<< orphan*/  tso_caps; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; } ;
struct mlx5_query_device_ex {int /*<<< orphan*/  cqe_comp_caps; scalar_t__ support_multi_pkt_send_wqe; TYPE_3__ packet_pacing_caps; TYPE_2__ rss_caps; int /*<<< orphan*/  tso_caps; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; } ;
struct mlx5_context {int cmds_supp_uhw; int /*<<< orphan*/  cqe_comp_caps; int /*<<< orphan*/  vendor_cap_flags; } ;
struct ibv_query_device_ex_input {int dummy; } ;
struct ibv_device_attr {int /*<<< orphan*/  fw_ver; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_hash_function; int /*<<< orphan*/  rx_hash_fields_mask; } ;
struct ibv_device_attr_ex {struct ibv_device_attr orig_attr; int /*<<< orphan*/  packet_pacing_caps; TYPE_1__ rss_caps; int /*<<< orphan*/  tso_caps; } ;
struct ibv_context {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int MLX5_USER_CMDS_SUPP_UHW_QUERY_DEVICE ; 
 int /*<<< orphan*/  MLX5_VENDOR_CAP_FLAGS_MPW ; 
 int ibv_cmd_query_device_ex (struct ibv_context*,struct ibv_query_device_ex_input const*,struct ibv_device_attr_ex*,size_t,int*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (struct mlx5_query_device_ex_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,unsigned int,unsigned int) ; 
 struct mlx5_context* to_mctx (struct ibv_context*) ; 

int mlx5_query_device_ex(struct ibv_context *context,
			 const struct ibv_query_device_ex_input *input,
			 struct ibv_device_attr_ex *attr,
			 size_t attr_size)
{
	struct mlx5_context *mctx = to_mctx(context);
	struct mlx5_query_device_ex_resp resp;
	struct mlx5_query_device_ex cmd;
	struct ibv_device_attr *a;
	uint64_t raw_fw_ver;
	unsigned sub_minor;
	unsigned major;
	unsigned minor;
	int err;
	int cmd_supp_uhw = mctx->cmds_supp_uhw &
		MLX5_USER_CMDS_SUPP_UHW_QUERY_DEVICE;

	memset(&cmd, 0, sizeof(cmd));
	memset(&resp, 0, sizeof(resp));
	err = ibv_cmd_query_device_ex(context, input, attr, attr_size,
				      &raw_fw_ver,
				      &cmd.ibv_cmd, sizeof(cmd.ibv_cmd), sizeof(cmd),
				      &resp.ibv_resp, sizeof(resp.ibv_resp),
				      cmd_supp_uhw ? sizeof(resp) : sizeof(resp.ibv_resp));
	if (err)
		return err;

	attr->tso_caps = resp.tso_caps;
	attr->rss_caps.rx_hash_fields_mask = resp.rss_caps.rx_hash_fields_mask;
	attr->rss_caps.rx_hash_function = resp.rss_caps.rx_hash_function;
	attr->packet_pacing_caps = resp.packet_pacing_caps.caps;

	if (resp.support_multi_pkt_send_wqe)
		mctx->vendor_cap_flags |= MLX5_VENDOR_CAP_FLAGS_MPW;

	mctx->cqe_comp_caps = resp.cqe_comp_caps;

	major     = (raw_fw_ver >> 32) & 0xffff;
	minor     = (raw_fw_ver >> 16) & 0xffff;
	sub_minor = raw_fw_ver & 0xffff;
	a = &attr->orig_attr;
	snprintf(a->fw_ver, sizeof(a->fw_ver), "%d.%d.%04d",
		 major, minor, sub_minor);

	return 0;
}