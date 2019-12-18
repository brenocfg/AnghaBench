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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_WPAR_IOBX (int) ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_l2c_get_num_assoc () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int cvmx_l2c_set_hw_way_partition2(uint32_t mask)
{
    uint32_t valid_mask;

        if (!OCTEON_IS_MODEL(OCTEON_CN68XX))
            return -1;

    valid_mask = (0x1 << cvmx_l2c_get_num_assoc()) - 1;
    mask &= valid_mask;
        cvmx_write_csr(CVMX_L2C_WPAR_IOBX(1), mask);
        return 0;
}