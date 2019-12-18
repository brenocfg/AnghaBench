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
 int qls_rd_mpi_reg (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int
qls_get_mpi_regs(qla_host_t *ha, uint32_t *buf, uint32_t offset, uint32_t count)
{
	int i, ret = 0;

	for (i = 0; i < count; i++, buf++) {

		ret = qls_rd_mpi_reg(ha, (offset + i), buf);

		if (ret)
			return ret;
	}

	return (ret);
}