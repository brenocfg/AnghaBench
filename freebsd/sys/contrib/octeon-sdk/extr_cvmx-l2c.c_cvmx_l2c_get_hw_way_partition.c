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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_SPAR4 ; 
 int /*<<< orphan*/  CVMX_L2C_WPAR_IOBX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 

int cvmx_l2c_get_hw_way_partition(void)
{
    if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
        return cvmx_read_csr(CVMX_L2C_WPAR_IOBX(0)) & 0xffff;
    else
        return cvmx_read_csr(CVMX_L2C_SPAR4) & (0xFF);
}