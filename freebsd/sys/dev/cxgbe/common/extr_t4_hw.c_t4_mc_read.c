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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int A_MC_BIST_CMD ; 
 int A_MC_BIST_CMD_ADDR ; 
 int A_MC_BIST_CMD_LEN ; 
 int A_MC_BIST_DATA_PATTERN ; 
 int A_MC_BIST_STATUS_RDATA ; 
 int /*<<< orphan*/  A_MC_P_BIST_CMD ; 
 int /*<<< orphan*/  A_MC_P_BIST_CMD_ADDR ; 
 int /*<<< orphan*/  A_MC_P_BIST_CMD_LEN ; 
 int /*<<< orphan*/  A_MC_P_BIST_DATA_PATTERN ; 
 int /*<<< orphan*/  A_MC_P_BIST_STATUS_RDATA ; 
 int EBUSY ; 
 int F_START_BIST ; 
 int MC_DATA (int) ; 
 int MC_REG (int /*<<< orphan*/ ,int) ; 
 int V_BIST_CMD_GAP (int) ; 
 int V_BIST_OPCODE (int) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  ntohl (int) ; 
 int t4_read_reg (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_read_reg64 (struct adapter*,int) ; 
 int t4_wait_op_done (struct adapter*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int) ; 

int t4_mc_read(struct adapter *adap, int idx, u32 addr, __be32 *data, u64 *ecc)
{
	int i;
	u32 mc_bist_cmd_reg, mc_bist_cmd_addr_reg, mc_bist_cmd_len_reg;
	u32 mc_bist_status_rdata_reg, mc_bist_data_pattern_reg;

	if (is_t4(adap)) {
		mc_bist_cmd_reg = A_MC_BIST_CMD;
		mc_bist_cmd_addr_reg = A_MC_BIST_CMD_ADDR;
		mc_bist_cmd_len_reg = A_MC_BIST_CMD_LEN;
		mc_bist_status_rdata_reg = A_MC_BIST_STATUS_RDATA;
		mc_bist_data_pattern_reg = A_MC_BIST_DATA_PATTERN;
	} else {
		mc_bist_cmd_reg = MC_REG(A_MC_P_BIST_CMD, idx);
		mc_bist_cmd_addr_reg = MC_REG(A_MC_P_BIST_CMD_ADDR, idx);
		mc_bist_cmd_len_reg = MC_REG(A_MC_P_BIST_CMD_LEN, idx);
		mc_bist_status_rdata_reg = MC_REG(A_MC_P_BIST_STATUS_RDATA,
						  idx);
		mc_bist_data_pattern_reg = MC_REG(A_MC_P_BIST_DATA_PATTERN,
						  idx);
	}

	if (t4_read_reg(adap, mc_bist_cmd_reg) & F_START_BIST)
		return -EBUSY;
	t4_write_reg(adap, mc_bist_cmd_addr_reg, addr & ~0x3fU);
	t4_write_reg(adap, mc_bist_cmd_len_reg, 64);
	t4_write_reg(adap, mc_bist_data_pattern_reg, 0xc);
	t4_write_reg(adap, mc_bist_cmd_reg, V_BIST_OPCODE(1) |
		     F_START_BIST | V_BIST_CMD_GAP(1));
	i = t4_wait_op_done(adap, mc_bist_cmd_reg, F_START_BIST, 0, 10, 1);
	if (i)
		return i;

#define MC_DATA(i) MC_BIST_STATUS_REG(mc_bist_status_rdata_reg, i)

	for (i = 15; i >= 0; i--)
		*data++ = ntohl(t4_read_reg(adap, MC_DATA(i)));
	if (ecc)
		*ecc = t4_read_reg64(adap, MC_DATA(16));
#undef MC_DATA
	return 0;
}