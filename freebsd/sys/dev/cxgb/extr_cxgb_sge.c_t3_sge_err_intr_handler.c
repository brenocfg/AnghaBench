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
 int /*<<< orphan*/  A_SG_INT_CAUSE ; 
 int /*<<< orphan*/  A_SG_RSPQ_FL_STATUS ; 
 int /*<<< orphan*/  CH_ALERT (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int F_RSPQCREDITOVERFOW ; 
 unsigned int F_RSPQDISABLED ; 
 unsigned int SGE_FATALERR ; 
 unsigned int SGE_FRAMINGERR ; 
 unsigned int SGE_PARERR ; 
 unsigned int S_RSPQ0DISABLED ; 
 int /*<<< orphan*/  t3_fatal_err (int /*<<< orphan*/ *) ; 
 unsigned int t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

void
t3_sge_err_intr_handler(adapter_t *adapter)
{
	unsigned int v, status;

	status = t3_read_reg(adapter, A_SG_INT_CAUSE);
	if (status & SGE_PARERR)
		CH_ALERT(adapter, "SGE parity error (0x%x)\n",
			 status & SGE_PARERR);
	if (status & SGE_FRAMINGERR)
		CH_ALERT(adapter, "SGE framing error (0x%x)\n",
			 status & SGE_FRAMINGERR);
	if (status & F_RSPQCREDITOVERFOW)
		CH_ALERT(adapter, "SGE response queue credit overflow\n");

	if (status & F_RSPQDISABLED) {
		v = t3_read_reg(adapter, A_SG_RSPQ_FL_STATUS);

		CH_ALERT(adapter,
			 "packet delivered to disabled response queue (0x%x)\n",
			 (v >> S_RSPQ0DISABLED) & 0xff);
	}

	t3_write_reg(adapter, A_SG_INT_CAUSE, status);
	if (status & SGE_FATALERR)
		t3_fatal_err(adapter);
}