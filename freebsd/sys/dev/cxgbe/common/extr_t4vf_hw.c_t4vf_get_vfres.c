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
struct vf_resources {int /*<<< orphan*/  nethctrl; int /*<<< orphan*/  wx_caps; int /*<<< orphan*/  r_caps; int /*<<< orphan*/  nexactf; int /*<<< orphan*/  nvi; int /*<<< orphan*/  tc; int /*<<< orphan*/  pmask; int /*<<< orphan*/  neq; int /*<<< orphan*/  niq; int /*<<< orphan*/  niqflint; } ;
struct fw_pfvf_cmd {int /*<<< orphan*/  r_caps_to_nethctrl; int /*<<< orphan*/  tc_to_nexactf; int /*<<< orphan*/  type_to_neq; int /*<<< orphan*/  niqflint_niq; void* retval_len16; void* op_to_vfn; } ;
struct TYPE_2__ {struct vf_resources vfres; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int FW_LEN16 (struct fw_pfvf_cmd) ; 
 int /*<<< orphan*/  FW_PFVF_CMD ; 
 int FW_SUCCESS ; 
 int F_FW_CMD_READ ; 
 int F_FW_CMD_REQUEST ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_NEQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_NETHCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_NEXACTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_NIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_NIQFLINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_NVI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_PMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_R_CAPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_TC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_PFVF_CMD_WX_CAPS (int /*<<< orphan*/ ) ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_pfvf_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_pfvf_cmd*,int,struct fw_pfvf_cmd*) ; 

int t4vf_get_vfres(struct adapter *adapter)
{
	struct vf_resources *vfres = &adapter->params.vfres;
	struct fw_pfvf_cmd cmd, rpl;
	int v;
	u32 word;

	/*
	 * Execute PFVF Read command to get VF resource limits; bail out early
	 * with error on command failure.
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(V_FW_CMD_OP(FW_PFVF_CMD) |
				    F_FW_CMD_REQUEST |
				    F_FW_CMD_READ);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	v = t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), &rpl);
	if (v != FW_SUCCESS)
		return v;

	/*
	 * Extract VF resource limits and return success.
	 */
	word = be32_to_cpu(rpl.niqflint_niq);
	vfres->niqflint = G_FW_PFVF_CMD_NIQFLINT(word);
	vfres->niq = G_FW_PFVF_CMD_NIQ(word);

	word = be32_to_cpu(rpl.type_to_neq);
	vfres->neq = G_FW_PFVF_CMD_NEQ(word);
	vfres->pmask = G_FW_PFVF_CMD_PMASK(word);

	word = be32_to_cpu(rpl.tc_to_nexactf);
	vfres->tc = G_FW_PFVF_CMD_TC(word);
	vfres->nvi = G_FW_PFVF_CMD_NVI(word);
	vfres->nexactf = G_FW_PFVF_CMD_NEXACTF(word);

	word = be32_to_cpu(rpl.r_caps_to_nethctrl);
	vfres->r_caps = G_FW_PFVF_CMD_R_CAPS(word);
	vfres->wx_caps = G_FW_PFVF_CMD_WX_CAPS(word);
	vfres->nethctrl = G_FW_PFVF_CMD_NETHCTRL(word);

	return 0;
}