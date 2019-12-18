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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q81_CTL_PROC_ADDR ; 
 int /*<<< orphan*/  Q81_CTL_PROC_DATA ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qls_wait_for_proc_addr_ready (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qls_proc_addr_wr_reg(qla_host_t *ha, uint32_t addr_module, uint32_t reg,
	uint32_t data)
{
	int ret;
	uint32_t value;

	ret = qls_wait_for_proc_addr_ready(ha);

	if (ret)
		goto qls_proc_addr_wr_reg_exit;

	WRITE_REG32(ha, Q81_CTL_PROC_DATA, data);

	value = addr_module | reg;

	WRITE_REG32(ha, Q81_CTL_PROC_ADDR, value);

	ret = qls_wait_for_proc_addr_ready(ha);

qls_proc_addr_wr_reg_exit:
	return (ret);
}