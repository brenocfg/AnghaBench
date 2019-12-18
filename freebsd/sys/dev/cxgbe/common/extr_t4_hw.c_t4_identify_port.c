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
struct fw_vi_enable_cmd {int /*<<< orphan*/  blinkdur; void* ien_to_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_LEN16 (struct fw_vi_enable_cmd) ; 
 int /*<<< orphan*/  FW_VI_ENABLE_CMD ; 
 int F_FW_CMD_EXEC ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_VI_ENABLE_CMD_LED ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_VI_ENABLE_CMD_VIID (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_vi_enable_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_vi_enable_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_identify_port(struct adapter *adap, unsigned int mbox, unsigned int viid,
		     unsigned int nblinks)
{
	struct fw_vi_enable_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_viid = cpu_to_be32(V_FW_CMD_OP(FW_VI_ENABLE_CMD) |
				   F_FW_CMD_REQUEST | F_FW_CMD_EXEC |
				   V_FW_VI_ENABLE_CMD_VIID(viid));
	c.ien_to_len16 = cpu_to_be32(F_FW_VI_ENABLE_CMD_LED | FW_LEN16(c));
	c.blinkdur = cpu_to_be16(nblinks);
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}