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
struct fw_devlog_cmd {unsigned int level; void* retval_len16; void* op_to_write; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  devlog_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DEVLOG_CMD ; 
 int FW_LEN16 (struct fw_devlog_cmd) ; 
 int F_FW_CMD_READ ; 
 int F_FW_CMD_REQUEST ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_devlog_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_devlog_cmd*,int,struct fw_devlog_cmd*) ; 

int t4_get_devlog_level(struct adapter *adapter, unsigned int *level)
{
	struct fw_devlog_cmd devlog_cmd;
	int ret;

	memset(&devlog_cmd, 0, sizeof(devlog_cmd));
	devlog_cmd.op_to_write = cpu_to_be32(V_FW_CMD_OP(FW_DEVLOG_CMD) |
					     F_FW_CMD_REQUEST | F_FW_CMD_READ);
	devlog_cmd.retval_len16 = cpu_to_be32(FW_LEN16(devlog_cmd));
	ret = t4_wr_mbox(adapter, adapter->mbox, &devlog_cmd,
			 sizeof(devlog_cmd), &devlog_cmd);
	if (ret)
		return ret;

	*level = devlog_cmd.level;
	return 0;
}