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
 int /*<<< orphan*/  Q81_CTL_HCS_CMD_CLR_RISC_PAUSE ; 
 int Q81_CTL_HCS_RISC_PAUSED ; 
 int /*<<< orphan*/  Q81_CTL_HOST_CMD_STATUS ; 
 int READ_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qls_unpause_mpi_risc(qla_host_t *ha)
{
	uint32_t data;

	data = READ_REG32(ha, Q81_CTL_HOST_CMD_STATUS);

	if (!(data & Q81_CTL_HCS_RISC_PAUSED))
		return -1;

	WRITE_REG32(ha, Q81_CTL_HOST_CMD_STATUS, \
		Q81_CTL_HCS_CMD_CLR_RISC_PAUSE);

	return 0;
}