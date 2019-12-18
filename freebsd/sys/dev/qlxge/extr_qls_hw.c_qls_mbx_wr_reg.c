#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int pci_func; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 scalar_t__ Q81_FUNC0_MBX_IN_REG0 ; 
 scalar_t__ Q81_FUNC1_MBX_IN_REG0 ; 
 int qls_mpi_risc_wr_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
qls_mbx_wr_reg(qla_host_t *ha, uint32_t reg, uint32_t data)
{
	int ret;

	if ((ha->pci_func & 0x1) == 0)
		reg += Q81_FUNC0_MBX_IN_REG0;
	else
		reg += Q81_FUNC1_MBX_IN_REG0;

	ret = qls_mpi_risc_wr_reg(ha, reg, data);

	return (ret);
}