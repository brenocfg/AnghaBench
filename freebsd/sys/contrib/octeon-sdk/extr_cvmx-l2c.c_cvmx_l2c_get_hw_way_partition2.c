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
 int /*<<< orphan*/  CVMX_L2C_WPAR_IOBX (int) ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_warn (char*) ; 

int cvmx_l2c_get_hw_way_partition2(void)
{
        if (!OCTEON_IS_MODEL(OCTEON_CN68XX)) {
            cvmx_warn("only one IOB on this chip");
            return -1;
        }
        return cvmx_read_csr(CVMX_L2C_WPAR_IOBX(1)) & 0xffff;
}