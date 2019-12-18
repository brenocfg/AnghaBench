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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {void* dest_type; int /*<<< orphan*/  priority; void* dest_id; } ;
struct dpseci_congestion_notification_cfg {void* threshold_exit; void* threshold_entry; void* message_ctx; void* message_iova; void* units; TYPE_1__ dest_cfg; int /*<<< orphan*/  notification_mode; } ;
struct dpseci_cmd_congestion_notification {int /*<<< orphan*/  threshold_exit; int /*<<< orphan*/  threshold_entry; int /*<<< orphan*/  message_ctx; int /*<<< orphan*/  message_iova; int /*<<< orphan*/  options; int /*<<< orphan*/  priority; int /*<<< orphan*/  notification_mode; int /*<<< orphan*/  dest_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGN_DEST_TYPE ; 
 int /*<<< orphan*/  CGN_UNITS ; 
 int /*<<< orphan*/  DPSECI_CMDID_GET_CONGESTION_NOTIFICATION ; 
 void* dpseci_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpseci_get_congestion_notification(struct fsl_mc_io *mc_io, u32 cmd_flags,
	u16 token, struct dpseci_congestion_notification_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpseci_cmd_congestion_notification *rsp_params;
	int err;

	cmd.header = mc_encode_cmd_header(
			DPSECI_CMDID_GET_CONGESTION_NOTIFICATION,
			cmd_flags,
			token);
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpseci_cmd_congestion_notification *)cmd.params;
	cfg->dest_cfg.dest_id = le32_to_cpu(rsp_params->dest_id);
	cfg->notification_mode = le16_to_cpu(rsp_params->notification_mode);
	cfg->dest_cfg.priority = rsp_params->priority;
	cfg->dest_cfg.dest_type = dpseci_get_field(rsp_params->options,
						   CGN_DEST_TYPE);
	cfg->units = dpseci_get_field(rsp_params->options, CGN_UNITS);
	cfg->message_iova = le64_to_cpu(rsp_params->message_iova);
	cfg->message_ctx = le64_to_cpu(rsp_params->message_ctx);
	cfg->threshold_entry = le32_to_cpu(rsp_params->threshold_entry);
	cfg->threshold_exit = le32_to_cpu(rsp_params->threshold_exit);

	return 0;
}