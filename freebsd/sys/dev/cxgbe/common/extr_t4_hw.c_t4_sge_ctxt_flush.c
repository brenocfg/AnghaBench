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
typedef  int u32 ;
struct TYPE_3__ {void* msg_ctxtflush; } ;
struct TYPE_4__ {TYPE_1__ idctxt; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  FW_LDST_ADDRSPC_SGE_EGRC ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 int F_FW_CMD_READ ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_LDST_CMD_CTXTFLUSH ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_LDST_CMD_ADDRSPACE (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 

int t4_sge_ctxt_flush(struct adapter *adap, unsigned int mbox)
{
	int ret;
	u32 ldst_addrspace;
	struct fw_ldst_cmd c;

	memset(&c, 0, sizeof(c));
	ldst_addrspace = V_FW_LDST_CMD_ADDRSPACE(FW_LDST_ADDRSPC_SGE_EGRC);
	c.op_to_addrspace = cpu_to_be32(V_FW_CMD_OP(FW_LDST_CMD) |
					F_FW_CMD_REQUEST | F_FW_CMD_READ |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.idctxt.msg_ctxtflush = cpu_to_be32(F_FW_LDST_CMD_CTXTFLUSH);

	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	return ret;
}