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
struct fw_iq_cmd {void* fl1id; void* fl0id; void* iqid; void* type_to_iqandstindex; void* alloc_to_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  FW_IQ_CMD ; 
 int FW_LEN16 (struct fw_iq_cmd) ; 
 int F_FW_CMD_EXEC ; 
 int F_FW_CMD_REQUEST ; 
 int F_FW_IQ_CMD_FREE ; 
 int V_FW_CMD_OP (int /*<<< orphan*/ ) ; 
 int V_FW_IQ_CMD_PFN (unsigned int) ; 
 int V_FW_IQ_CMD_TYPE (unsigned int) ; 
 int V_FW_IQ_CMD_VFN (unsigned int) ; 
 void* cpu_to_be16 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_iq_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_iq_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_iq_free(struct adapter *adap, unsigned int mbox, unsigned int pf,
	       unsigned int vf, unsigned int iqtype, unsigned int iqid,
	       unsigned int fl0id, unsigned int fl1id)
{
	struct fw_iq_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = cpu_to_be32(V_FW_CMD_OP(FW_IQ_CMD) | F_FW_CMD_REQUEST |
				  F_FW_CMD_EXEC | V_FW_IQ_CMD_PFN(pf) |
				  V_FW_IQ_CMD_VFN(vf));
	c.alloc_to_len16 = cpu_to_be32(F_FW_IQ_CMD_FREE | FW_LEN16(c));
	c.type_to_iqandstindex = cpu_to_be32(V_FW_IQ_CMD_TYPE(iqtype));
	c.iqid = cpu_to_be16(iqid);
	c.fl0id = cpu_to_be16(fl0id);
	c.fl1id = cpu_to_be16(fl1id);
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}