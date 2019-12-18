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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpseci_tx_queue_attr {int /*<<< orphan*/  priority; int /*<<< orphan*/  fqid; } ;
struct dpseci_rsp_get_tx_queue {int /*<<< orphan*/  priority; int /*<<< orphan*/  fqid; } ;
struct dpseci_cmd_queue {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSECI_CMDID_GET_TX_QUEUE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpseci_get_tx_queue(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 queue, struct dpseci_tx_queue_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpseci_cmd_queue *cmd_params;
	struct dpseci_rsp_get_tx_queue *rsp_params;
	int err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_TX_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpseci_cmd_queue *)cmd.params;
	cmd_params->queue = queue;
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpseci_rsp_get_tx_queue *)cmd.params;
	attr->fqid = le32_to_cpu(rsp_params->fqid);
	attr->priority = rsp_params->priority;

	return 0;
}