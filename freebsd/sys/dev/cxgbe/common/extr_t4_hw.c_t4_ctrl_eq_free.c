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
struct fw_eq_ctrl_cmd {void* cmpliqid_eqid; void* alloc_to_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  FW_EQ_CTRL_CMD ; 
 int FW_LEN16 (struct fw_eq_ctrl_cmd) ; 
 int F_FW_CMD_EXEC ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_EQ_CTRL_CMD_FREE ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_EQ_CTRL_CMD_EQID (unsigned int) ; 
 int V_FW_EQ_CTRL_CMD_PFN (unsigned int) ; 
 int V_FW_EQ_CTRL_CMD_VFN (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_eq_ctrl_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_eq_ctrl_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_ctrl_eq_free(struct adapter *adap, unsigned int mbox, unsigned int pf,
		    unsigned int vf, unsigned int eqid)
{
	struct fw_eq_ctrl_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = cpu_to_be32(V_FW_CMD_OP(FW_EQ_CTRL_CMD) |
				  F_FW_CMD_REQUEST | F_FW_CMD_EXEC |
				  V_FW_EQ_CTRL_CMD_PFN(pf) |
				  V_FW_EQ_CTRL_CMD_VFN(vf));
	c.alloc_to_len16 = cpu_to_be32(F_FW_EQ_CTRL_CMD_FREE | FW_LEN16(c));
	c.cmpliqid_eqid = cpu_to_be32(V_FW_EQ_CTRL_CMD_EQID(eqid));
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}