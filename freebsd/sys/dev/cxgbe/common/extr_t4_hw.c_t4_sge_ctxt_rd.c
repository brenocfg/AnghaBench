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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  ctxt_data5; int /*<<< orphan*/  ctxt_data4; int /*<<< orphan*/  ctxt_data3; int /*<<< orphan*/  ctxt_data2; int /*<<< orphan*/  ctxt_data1; int /*<<< orphan*/  ctxt_data0; void* physid; } ;
struct TYPE_4__ {TYPE_1__ idctxt; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int dummy; } ;
typedef  enum ctxt_type { ____Placeholder_ctxt_type } ctxt_type ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int CTXT_EGRESS ; 
 int CTXT_FLM ; 
 int CTXT_INGRESS ; 
 int FW_LDST_ADDRSPC_SGE_CONMC ; 
 int FW_LDST_ADDRSPC_SGE_EGRC ; 
 int FW_LDST_ADDRSPC_SGE_FLMC ; 
 int FW_LDST_ADDRSPC_SGE_INGC ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 unsigned int FW_LEN16 (struct fw_ldst_cmd) ; 
 unsigned int F_FW_CMD_READ ; 
 unsigned int F_FW_CMD_REQUEST ; 
 unsigned int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 unsigned int V_FW_LDST_CMD_ADDRSPACE (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 

int t4_sge_ctxt_rd(struct adapter *adap, unsigned int mbox, unsigned int cid,
		   enum ctxt_type ctype, u32 *data)
{
	int ret;
	struct fw_ldst_cmd c;

	if (ctype == CTXT_EGRESS)
		ret = FW_LDST_ADDRSPC_SGE_EGRC;
	else if (ctype == CTXT_INGRESS)
		ret = FW_LDST_ADDRSPC_SGE_INGC;
	else if (ctype == CTXT_FLM)
		ret = FW_LDST_ADDRSPC_SGE_FLMC;
	else
		ret = FW_LDST_ADDRSPC_SGE_CONMC;

	memset(&c, 0, sizeof(c));
	c.op_to_addrspace = cpu_to_be32(V_FW_CMD_OP(FW_LDST_CMD) |
					F_FW_CMD_REQUEST | F_FW_CMD_READ |
					V_FW_LDST_CMD_ADDRSPACE(ret));
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.idctxt.physid = cpu_to_be32(cid);

	ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), &c);
	if (ret == 0) {
		data[0] = be32_to_cpu(c.u.idctxt.ctxt_data0);
		data[1] = be32_to_cpu(c.u.idctxt.ctxt_data1);
		data[2] = be32_to_cpu(c.u.idctxt.ctxt_data2);
		data[3] = be32_to_cpu(c.u.idctxt.ctxt_data3);
		data[4] = be32_to_cpu(c.u.idctxt.ctxt_data4);
		data[5] = be32_to_cpu(c.u.idctxt.ctxt_data5);
	}
	return ret;
}