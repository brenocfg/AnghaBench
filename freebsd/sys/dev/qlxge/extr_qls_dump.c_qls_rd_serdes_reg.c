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
 int /*<<< orphan*/  Q81_CTL_XG_SERDES_ADDR ; 
 int /*<<< orphan*/  Q81_CTL_XG_SERDES_DATA ; 
 int /*<<< orphan*/  Q81_XG_SERDES_ADDR_RDY ; 
 int Q81_XG_SERDES_ADDR_READ ; 
 int READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qls_wait_reg_rdy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qls_rd_serdes_reg(qla_host_t *ha, uint32_t reg, uint32_t *data)
{
	int ret;

	ret = qls_wait_reg_rdy(ha, Q81_CTL_XG_SERDES_ADDR,
			Q81_XG_SERDES_ADDR_RDY, 0);

	if (ret)
		goto exit_qls_rd_serdes_reg;

	WRITE_REG32(ha, Q81_CTL_XG_SERDES_ADDR, \
		(reg | Q81_XG_SERDES_ADDR_READ));

	ret = qls_wait_reg_rdy(ha, Q81_CTL_XG_SERDES_ADDR,
			Q81_XG_SERDES_ADDR_RDY, 0);

	if (ret)
		goto exit_qls_rd_serdes_reg;

	*data = READ_REG32(ha, Q81_CTL_XG_SERDES_DATA);

exit_qls_rd_serdes_reg:

	return ret;
}