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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpseci_rsp_get_attributes {int /*<<< orphan*/  options; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  num_tx_queues; int /*<<< orphan*/  id; } ;
struct dpseci_attr {void* options; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  num_tx_queues; void* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSECI_CMDID_GET_ATTR ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpseci_get_attributes(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  struct dpseci_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpseci_rsp_get_attributes *rsp_params;
	int err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_ATTR,
					  cmd_flags,
					  token);
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpseci_rsp_get_attributes *)cmd.params;
	attr->id = le32_to_cpu(rsp_params->id);
	attr->num_tx_queues = rsp_params->num_tx_queues;
	attr->num_rx_queues = rsp_params->num_rx_queues;
	attr->options = le32_to_cpu(rsp_params->options);

	return 0;
}