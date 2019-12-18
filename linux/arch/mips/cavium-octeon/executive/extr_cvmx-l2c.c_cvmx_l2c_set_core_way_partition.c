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
 int /*<<< orphan*/  CVMX_L2C_SPAR0 ; 
 int /*<<< orphan*/  CVMX_L2C_SPAR1 ; 
 int /*<<< orphan*/  CVMX_L2C_SPAR2 ; 
 int /*<<< orphan*/  CVMX_L2C_SPAR3 ; 
 int /*<<< orphan*/  CVMX_L2C_WPAR_PPX (int) ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_l2c_get_num_assoc () ; 
 int cvmx_octeon_num_cores () ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int cvmx_l2c_set_core_way_partition(uint32_t core, uint32_t mask)
{
	uint32_t field;
	uint32_t valid_mask;

	valid_mask = (0x1 << cvmx_l2c_get_num_assoc()) - 1;

	mask &= valid_mask;

	/* A UMSK setting which blocks all L2C Ways is an error on some chips */
	if (mask == valid_mask && !OCTEON_IS_MODEL(OCTEON_CN63XX))
		return -1;

	/* Validate the core number */
	if (core >= cvmx_octeon_num_cores())
		return -1;

	if (OCTEON_IS_MODEL(OCTEON_CN63XX)) {
		cvmx_write_csr(CVMX_L2C_WPAR_PPX(core), mask);
		return 0;
	}

	/*
	 * Use the lower two bits of core to determine the bit offset of the
	 * UMSK[] field in the L2C_SPAR register.
	 */
	field = (core & 0x3) * 8;

	/*
	 * Assign the new mask setting to the UMSK[] field in the appropriate
	 * L2C_SPAR register based on the core_num.
	 *
	 */
	switch (core & 0xC) {
	case 0x0:
		cvmx_write_csr(CVMX_L2C_SPAR0,
			       (cvmx_read_csr(CVMX_L2C_SPAR0) & ~(0xFF << field)) |
			       mask << field);
		break;
	case 0x4:
		cvmx_write_csr(CVMX_L2C_SPAR1,
			       (cvmx_read_csr(CVMX_L2C_SPAR1) & ~(0xFF << field)) |
			       mask << field);
		break;
	case 0x8:
		cvmx_write_csr(CVMX_L2C_SPAR2,
			       (cvmx_read_csr(CVMX_L2C_SPAR2) & ~(0xFF << field)) |
			       mask << field);
		break;
	case 0xC:
		cvmx_write_csr(CVMX_L2C_SPAR3,
			       (cvmx_read_csr(CVMX_L2C_SPAR3) & ~(0xFF << field)) |
			       mask << field);
		break;
	}
	return 0;
}