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
struct TYPE_3__ {int ch; int rate; void* max; int /*<<< orphan*/  level; int /*<<< orphan*/  type; int /*<<< orphan*/  sc; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct fw_sched_cmd {TYPE_2__ u; void* retval_len16; void* op_to_write; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 unsigned int FW_LEN16 (struct fw_sched_cmd) ; 
 int /*<<< orphan*/  FW_SCHED_CMD ; 
 int /*<<< orphan*/  FW_SCHED_PARAMS_LEVEL_CH_RL ; 
 int /*<<< orphan*/  FW_SCHED_SC_PARAMS ; 
 int /*<<< orphan*/  FW_SCHED_TYPE_PKTSCHED ; 
 unsigned int F_FW_CMD_REQUEST ; 
 unsigned int F_FW_CMD_WRITE ; 
 unsigned int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_sched_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox_meat (struct adapter*,int /*<<< orphan*/ ,struct fw_sched_cmd*,int,int /*<<< orphan*/ *,int) ; 

int t4_sched_params_ch_rl(struct adapter *adapter, int channel, int ratemode,
    unsigned int maxrate, int sleep_ok)
{
	struct fw_sched_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_write = cpu_to_be32(V_FW_CMD_OP(FW_SCHED_CMD) |
				      F_FW_CMD_REQUEST |
				      F_FW_CMD_WRITE);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));

	cmd.u.params.sc = FW_SCHED_SC_PARAMS;
	cmd.u.params.type = FW_SCHED_TYPE_PKTSCHED;
	cmd.u.params.level = FW_SCHED_PARAMS_LEVEL_CH_RL;
	cmd.u.params.ch = channel;
	cmd.u.params.rate = ratemode;		/* REL or ABS */
	cmd.u.params.max = cpu_to_be32(maxrate);/*  %  or kbps */

	return t4_wr_mbox_meat(adapter,adapter->mbox, &cmd, sizeof(cmd),
			       NULL, sleep_ok);
}