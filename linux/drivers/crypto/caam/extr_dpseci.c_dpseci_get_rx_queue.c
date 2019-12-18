#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {void* dest_type; int /*<<< orphan*/  priority; void* dest_id; } ;
struct dpseci_rx_queue_attr {void* order_preservation_en; void* fqid; int /*<<< orphan*/  user_ctx; TYPE_1__ dest_cfg; } ;
struct dpseci_cmd_queue {int /*<<< orphan*/  order_preservation_en; int /*<<< orphan*/  fqid; int /*<<< orphan*/  user_ctx; int /*<<< orphan*/  dest_type; int /*<<< orphan*/  priority; int /*<<< orphan*/  dest_id; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEST_TYPE ; 
 int /*<<< orphan*/  DPSECI_CMDID_GET_RX_QUEUE ; 
 int /*<<< orphan*/  ORDER_PRESERVATION ; 
 void* dpseci_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpseci_get_rx_queue(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 queue, struct dpseci_rx_queue_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpseci_cmd_queue *cmd_params;
	int err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_RX_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpseci_cmd_queue *)cmd.params;
	cmd_params->queue = queue;
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	attr->dest_cfg.dest_id = le32_to_cpu(cmd_params->dest_id);
	attr->dest_cfg.priority = cmd_params->priority;
	attr->dest_cfg.dest_type = dpseci_get_field(cmd_params->dest_type,
						    DEST_TYPE);
	attr->user_ctx = le64_to_cpu(cmd_params->user_ctx);
	attr->fqid = le32_to_cpu(cmd_params->fqid);
	attr->order_preservation_en =
		dpseci_get_field(cmd_params->order_preservation_en,
				 ORDER_PRESERVATION);

	return 0;
}