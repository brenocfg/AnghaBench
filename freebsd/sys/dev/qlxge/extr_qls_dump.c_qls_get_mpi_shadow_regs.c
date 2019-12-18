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
 int Q81_CTL_PROC_ADDR_RISC_INT_REG ; 
 int Q81_MPI_CORE_SH_REGS_CNT ; 
 int Q81_RISC_124 ; 
 int Q81_RISC_127 ; 
 int Q81_SHADOW_OFFSET ; 
 int qls_mpi_risc_rd_reg (int /*<<< orphan*/ *,int,int*) ; 
 int qls_wr_mpi_reg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
qls_get_mpi_shadow_regs(qla_host_t *ha, uint32_t *buf)
{
	uint32_t	i;
	int		ret;

#define Q81_RISC_124 0x0000007c
#define Q81_RISC_127 0x0000007f
#define Q81_SHADOW_OFFSET 0xb0000000

	for (i = 0; i < Q81_MPI_CORE_SH_REGS_CNT; i++, buf++) {

		ret = qls_wr_mpi_reg(ha,
				(Q81_CTL_PROC_ADDR_RISC_INT_REG | Q81_RISC_124),
                                (Q81_SHADOW_OFFSET | i << 20));
		if (ret)
			goto exit_qls_get_mpi_shadow_regs;

		ret = qls_mpi_risc_rd_reg(ha,
				(Q81_CTL_PROC_ADDR_RISC_INT_REG | Q81_RISC_127),
				 buf);
		if (ret)
			goto exit_qls_get_mpi_shadow_regs;
	}

exit_qls_get_mpi_shadow_regs:
	return ret;
}