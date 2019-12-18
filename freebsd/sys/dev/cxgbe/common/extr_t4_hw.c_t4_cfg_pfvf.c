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
struct fw_pfvf_cmd {void* r_caps_to_nethctrl; void* tc_to_nexactf; void* type_to_neq; void* niqflint_niq; void* retval_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_LEN16 (struct fw_pfvf_cmd) ; 
 int /*<<< orphan*/  FW_PFVF_CMD ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_CMD_WRITE ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_PFVF_CMD_CMASK (unsigned int) ; 
 int V_FW_PFVF_CMD_NEQ (unsigned int) ; 
 int V_FW_PFVF_CMD_NETHCTRL (unsigned int) ; 
 int V_FW_PFVF_CMD_NEXACTF (unsigned int) ; 
 int V_FW_PFVF_CMD_NIQ (unsigned int) ; 
 int V_FW_PFVF_CMD_NIQFLINT (unsigned int) ; 
 int V_FW_PFVF_CMD_NVI (unsigned int) ; 
 int V_FW_PFVF_CMD_PFN (unsigned int) ; 
 int V_FW_PFVF_CMD_PMASK (unsigned int) ; 
 int V_FW_PFVF_CMD_R_CAPS (unsigned int) ; 
 int V_FW_PFVF_CMD_TC (unsigned int) ; 
 int V_FW_PFVF_CMD_VFN (unsigned int) ; 
 int V_FW_PFVF_CMD_WX_CAPS (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_pfvf_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_pfvf_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_cfg_pfvf(struct adapter *adap, unsigned int mbox, unsigned int pf,
		unsigned int vf, unsigned int txq, unsigned int txq_eth_ctrl,
		unsigned int rxqi, unsigned int rxq, unsigned int tc,
		unsigned int vi, unsigned int cmask, unsigned int pmask,
		unsigned int nexact, unsigned int rcaps, unsigned int wxcaps)
{
	struct fw_pfvf_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = cpu_to_be32(V_FW_CMD_OP(FW_PFVF_CMD) | F_FW_CMD_REQUEST |
				  F_FW_CMD_WRITE | V_FW_PFVF_CMD_PFN(pf) |
				  V_FW_PFVF_CMD_VFN(vf));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.niqflint_niq = cpu_to_be32(V_FW_PFVF_CMD_NIQFLINT(rxqi) |
				     V_FW_PFVF_CMD_NIQ(rxq));
	c.type_to_neq = cpu_to_be32(V_FW_PFVF_CMD_CMASK(cmask) |
				    V_FW_PFVF_CMD_PMASK(pmask) |
				    V_FW_PFVF_CMD_NEQ(txq));
	c.tc_to_nexactf = cpu_to_be32(V_FW_PFVF_CMD_TC(tc) |
				      V_FW_PFVF_CMD_NVI(vi) |
				      V_FW_PFVF_CMD_NEXACTF(nexact));
	c.r_caps_to_nethctrl = cpu_to_be32(V_FW_PFVF_CMD_R_CAPS(rcaps) |
				     V_FW_PFVF_CMD_WX_CAPS(wxcaps) |
				     V_FW_PFVF_CMD_NETHCTRL(txq_eth_ctrl));
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}