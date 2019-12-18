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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTEXT_CMD ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA0 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA1 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA2 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA3 ; 
 int EBUSY ; 
 int EIO ; 
 int F_CONTEXT_CMD_BUSY ; 
 int /*<<< orphan*/  SG_CONTEXT_CMD_ATTEMPTS ; 
 unsigned int V_CONTEXT (unsigned int) ; 
 unsigned int V_CONTEXT_CMD_OPCODE (int /*<<< orphan*/ ) ; 
 int t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ t3_wait_op_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int t3_sge_read_context(unsigned int type, adapter_t *adapter,
			       unsigned int id, u32 data[4])
{
	if (t3_read_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		return -EBUSY;

	t3_write_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(0) | type | V_CONTEXT(id));
	if (t3_wait_op_done(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY, 0,
			    SG_CONTEXT_CMD_ATTEMPTS, 1))
		return -EIO;
	data[0] = t3_read_reg(adapter, A_SG_CONTEXT_DATA0);
	data[1] = t3_read_reg(adapter, A_SG_CONTEXT_DATA1);
	data[2] = t3_read_reg(adapter, A_SG_CONTEXT_DATA2);
	data[3] = t3_read_reg(adapter, A_SG_CONTEXT_DATA3);
	return 0;
}