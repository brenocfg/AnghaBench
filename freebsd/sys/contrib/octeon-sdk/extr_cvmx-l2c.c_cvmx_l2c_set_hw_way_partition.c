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
 int /*<<< orphan*/  CVMX_L2C_SPAR4 ; 
 int /*<<< orphan*/  CVMX_L2C_WPAR_IOBX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_l2c_get_num_assoc () ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int cvmx_l2c_set_hw_way_partition(uint32_t mask)
{
    uint32_t valid_mask;

    valid_mask = (0x1 << cvmx_l2c_get_num_assoc()) - 1;
    mask &= valid_mask;

    /* A UMSK setting which blocks all L2C Ways is an error on some chips */
    if (mask == valid_mask  && (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN5XXX)))
        return -1;

    if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
        cvmx_write_csr(CVMX_L2C_WPAR_IOBX(0), mask);
    else
        cvmx_write_csr(CVMX_L2C_SPAR4,
                   (cvmx_read_csr(CVMX_L2C_SPAR4) & ~0xFF) | mask);
    return 0;
}