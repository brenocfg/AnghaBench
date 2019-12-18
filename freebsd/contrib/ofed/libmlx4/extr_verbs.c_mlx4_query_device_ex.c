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
typedef  int uint64_t ;
struct mlx4_query_device_ex_resp {int comp_mask; int /*<<< orphan*/  hca_core_clock_offset; int /*<<< orphan*/  ibv_resp; } ;
struct mlx4_query_device_ex {int /*<<< orphan*/  ibv_cmd; } ;
struct TYPE_3__ {int offset_valid; int /*<<< orphan*/  offset; } ;
struct mlx4_context {TYPE_1__ core_clock; } ;
struct ibv_query_device_ex_input {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_ver; } ;
struct ibv_device_attr_ex {TYPE_2__ orig_attr; } ;
struct ibv_context {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int MLX4_QUERY_DEV_RESP_MASK_CORE_CLOCK_OFFSET ; 
 int ibv_cmd_query_device_ex (struct ibv_context*,struct ibv_query_device_ex_input const*,struct ibv_device_attr_ex*,size_t,int*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,unsigned int,unsigned int) ; 
 struct mlx4_context* to_mctx (struct ibv_context*) ; 

int mlx4_query_device_ex(struct ibv_context *context,
			 const struct ibv_query_device_ex_input *input,
			 struct ibv_device_attr_ex *attr,
			 size_t attr_size)
{
	struct mlx4_context *mctx = to_mctx(context);
	struct mlx4_query_device_ex_resp resp = {};
	struct mlx4_query_device_ex cmd = {};
	uint64_t raw_fw_ver;
	unsigned sub_minor;
	unsigned major;
	unsigned minor;
	int err;

	err = ibv_cmd_query_device_ex(context, input, attr, attr_size,
				      &raw_fw_ver,
				      &cmd.ibv_cmd, sizeof(cmd.ibv_cmd), sizeof(cmd),
				      &resp.ibv_resp, sizeof(resp.ibv_resp),
				      sizeof(resp));
	if (err)
		return err;

	if (resp.comp_mask & MLX4_QUERY_DEV_RESP_MASK_CORE_CLOCK_OFFSET) {
		mctx->core_clock.offset = resp.hca_core_clock_offset;
		mctx->core_clock.offset_valid = 1;
	}

	major     = (raw_fw_ver >> 32) & 0xffff;
	minor     = (raw_fw_ver >> 16) & 0xffff;
	sub_minor = raw_fw_ver & 0xffff;

	snprintf(attr->orig_attr.fw_ver, sizeof attr->orig_attr.fw_ver,
		 "%d.%d.%03d", major, minor, sub_minor);

	return 0;
}