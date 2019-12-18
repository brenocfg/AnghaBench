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
struct TYPE_2__ {int /*<<< orphan*/  dest_type; int /*<<< orphan*/  priority; int /*<<< orphan*/  dest_id; } ;
struct dpseci_rx_queue_cfg {int /*<<< orphan*/  order_preservation_en; int /*<<< orphan*/  options; int /*<<< orphan*/  user_ctx; TYPE_1__ dest_cfg; } ;
struct dpseci_cmd_queue {int /*<<< orphan*/  order_preservation_en; void* options; int /*<<< orphan*/  user_ctx; int /*<<< orphan*/  dest_type; int /*<<< orphan*/  queue; int /*<<< orphan*/  priority; void* dest_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEST_TYPE ; 
 int /*<<< orphan*/  DPSECI_CMDID_SET_RX_QUEUE ; 
 int /*<<< orphan*/  ORDER_PRESERVATION ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpseci_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpseci_set_rx_queue(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 queue, const struct dpseci_rx_queue_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpseci_cmd_queue *cmd_params;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_SET_RX_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpseci_cmd_queue *)cmd.params;
	cmd_params->dest_id = cpu_to_le32(cfg->dest_cfg.dest_id);
	cmd_params->priority = cfg->dest_cfg.priority;
	cmd_params->queue = queue;
	dpseci_set_field(cmd_params->dest_type, DEST_TYPE,
			 cfg->dest_cfg.dest_type);
	cmd_params->user_ctx = cpu_to_le64(cfg->user_ctx);
	cmd_params->options = cpu_to_le32(cfg->options);
	dpseci_set_field(cmd_params->order_preservation_en, ORDER_PRESERVATION,
			 cfg->order_preservation_en);

	return mc_send_command(mc_io, &cmd);
}