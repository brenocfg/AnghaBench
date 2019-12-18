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
typedef  unsigned int u32 ;
struct TYPE_3__ {void* val; void* addr; } ;
struct TYPE_4__ {TYPE_1__ addrval; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  FW_LDST_CMD ; 
 unsigned int FW_LEN16 (struct fw_ldst_cmd) ; 
 unsigned int F_FW_CMD_READ ; 
 unsigned int F_FW_CMD_REQUEST ; 
 unsigned int F_FW_CMD_WRITE ; 
 unsigned int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 unsigned int V_FW_LDST_CMD_ADDRSPACE (int) ; 
 unsigned int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox_meat (struct adapter*,int /*<<< orphan*/ ,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*,int) ; 

__attribute__((used)) static int t4_tp_fw_ldst_rw(struct adapter *adap, int cmd, u32 *vals,
			    unsigned int nregs, unsigned int start_index,
			    unsigned int rw, bool sleep_ok)
{
	int ret = 0;
	unsigned int i;
	struct fw_ldst_cmd c;

	for (i = 0; i < nregs; i++) {
		memset(&c, 0, sizeof(c));
		c.op_to_addrspace = cpu_to_be32(V_FW_CMD_OP(FW_LDST_CMD) |
						F_FW_CMD_REQUEST |
						(rw ? F_FW_CMD_READ :
						      F_FW_CMD_WRITE) |
						V_FW_LDST_CMD_ADDRSPACE(cmd));
		c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));

		c.u.addrval.addr = cpu_to_be32(start_index + i);
		c.u.addrval.val  = rw ? 0 : cpu_to_be32(vals[i]);
		ret = t4_wr_mbox_meat(adap, adap->mbox, &c, sizeof(c), &c,
				      sleep_ok);
		if (ret)
			return ret;

		if (rw)
			vals[i] = be32_to_cpu(c.u.addrval.val);
	}
	return 0;
}