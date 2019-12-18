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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q81_CTL_PROC_ADDR_MPI_RISC ; 
 int qls_proc_addr_wr_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
qls_mpi_risc_wr_reg(qla_host_t *ha, uint32_t reg, uint32_t data)
{
	int ret;

	ret = qls_proc_addr_wr_reg(ha, Q81_CTL_PROC_ADDR_MPI_RISC,
			reg, data);
	return (ret);
}