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
 int /*<<< orphan*/  Q81_CTL_FLASH_ADDR ; 
 int Q81_CTL_FLASH_ADDR_R ; 
 int /*<<< orphan*/  Q81_CTL_FLASH_DATA ; 
 int READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qls_wait_for_flash_ready (int /*<<< orphan*/ *) ; 

int
qls_rd_flash32(qla_host_t *ha, uint32_t addr, uint32_t *data)
{
	int ret;

	ret = qls_wait_for_flash_ready(ha);

	if (ret)
		return (ret);

	WRITE_REG32(ha, Q81_CTL_FLASH_ADDR, (addr | Q81_CTL_FLASH_ADDR_R));

	ret = qls_wait_for_flash_ready(ha);

	if (ret)
		return (ret);

	*data = READ_REG32(ha, Q81_CTL_FLASH_DATA);

	return 0;
}