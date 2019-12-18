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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTEXT_CMD ; 
 int /*<<< orphan*/  A_SG_CONTEXT_DATA0 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK0 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK1 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK2 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK3 ; 
 int EBUSY ; 
 int F_CONTEXT_CMD_BUSY ; 
 int F_CQ ; 
 int /*<<< orphan*/  M_CQ_SIZE ; 
 int /*<<< orphan*/  SG_CONTEXT_CMD_ATTEMPTS ; 
 int V_CONTEXT (unsigned int) ; 
 int V_CONTEXT_CMD_OPCODE (int) ; 
 int V_CQ_SIZE (int /*<<< orphan*/ ) ; 
 int t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int t3_sge_disable_cqcntxt(adapter_t *adapter, unsigned int id)
{
	if (t3_read_reg(adapter, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		return -EBUSY;

	t3_write_reg(adapter, A_SG_CONTEXT_MASK0, V_CQ_SIZE(M_CQ_SIZE));
	t3_write_reg(adapter, A_SG_CONTEXT_MASK1, 0);
	t3_write_reg(adapter, A_SG_CONTEXT_MASK2, 0);
	t3_write_reg(adapter, A_SG_CONTEXT_MASK3, 0);
	t3_write_reg(adapter, A_SG_CONTEXT_DATA0, 0);
	t3_write_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_CQ | V_CONTEXT(id));
	return t3_wait_op_done(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}