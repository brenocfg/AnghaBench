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
struct TYPE_3__ {int ctrl_to_fn; int r; int /*<<< orphan*/ * data; int /*<<< orphan*/  select_naccess; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int /*<<< orphan*/  mbox; int /*<<< orphan*/  pf; } ;
typedef  int /*<<< orphan*/  ldst_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,int,int) ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_FUNC_PCIE ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 int F_FW_CMD_READ ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_LDST_CMD_LC ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_LDST_CMD_ADDRSPACE (int /*<<< orphan*/ ) ; 
 int V_FW_LDST_CMD_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_FW_LDST_CMD_NACCESS (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_hw_pci_read_cfg4 (struct adapter*,int) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 

u32 t4_read_pcie_cfg4(struct adapter *adap, int reg, int drv_fw_attach)
{

	/*
	 * If fw_attach != 0, construct and send the Firmware LDST Command to
	 * retrieve the specified PCI-E Configuration Space register.
	 */
	if (drv_fw_attach != 0) {
		struct fw_ldst_cmd ldst_cmd;
		int ret;

		memset(&ldst_cmd, 0, sizeof(ldst_cmd));
		ldst_cmd.op_to_addrspace =
			cpu_to_be32(V_FW_CMD_OP(FW_LDST_CMD) |
				    F_FW_CMD_REQUEST |
				    F_FW_CMD_READ |
				    V_FW_LDST_CMD_ADDRSPACE(FW_LDST_ADDRSPC_FUNC_PCIE));
		ldst_cmd.cycles_to_len16 = cpu_to_be32(FW_LEN16(ldst_cmd));
		ldst_cmd.u.pcie.select_naccess = V_FW_LDST_CMD_NACCESS(1);
		ldst_cmd.u.pcie.ctrl_to_fn =
			(F_FW_LDST_CMD_LC | V_FW_LDST_CMD_FN(adap->pf));
		ldst_cmd.u.pcie.r = reg;

		/*
		 * If the LDST Command succeeds, return the result, otherwise
		 * fall through to reading it directly ourselves ...
		 */
		ret = t4_wr_mbox(adap, adap->mbox, &ldst_cmd, sizeof(ldst_cmd),
				 &ldst_cmd);
		if (ret == 0)
			return be32_to_cpu(ldst_cmd.u.pcie.data[0]);

		CH_WARN(adap, "Firmware failed to return "
			"Configuration Space register %d, err = %d\n",
			reg, -ret);
	}

	/*
	 * Read the desired Configuration Space register via the PCI-E
	 * Backdoor mechanism.
	 */
	return t4_hw_pci_read_cfg4(adap, reg);
}