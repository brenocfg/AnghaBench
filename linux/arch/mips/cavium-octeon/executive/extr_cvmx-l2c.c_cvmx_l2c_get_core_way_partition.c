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
 int cvmx_octeon_num_cores () ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 

int cvmx_l2c_get_core_way_partition(uint32_t core)
{
	uint32_t field;

	/* Validate the core number */
	if (core >= cvmx_octeon_num_cores())
		return -1;

	if (OCTEON_IS_MODEL(OCTEON_CN63XX))
		return cvmx_read_csr(CVMX_L2C_WPAR_PPX(core)) & 0xffff;

	/*
	 * Use the lower two bits of the coreNumber to determine the
	 * bit offset of the UMSK[] field in the L2C_SPAR register.
	 */
	field = (core & 0x3) * 8;

	/*
	 * Return the UMSK[] field from the appropriate L2C_SPAR
	 * register based on the coreNumber.
	 */

	switch (core & 0xC) {
	case 0x0:
		return (cvmx_read_csr(CVMX_L2C_SPAR0) & (0xFF << field)) >> field;
	case 0x4:
		return (cvmx_read_csr(CVMX_L2C_SPAR1) & (0xFF << field)) >> field;
	case 0x8:
		return (cvmx_read_csr(CVMX_L2C_SPAR2) & (0xFF << field)) >> field;
	case 0xC:
		return (cvmx_read_csr(CVMX_L2C_SPAR3) & (0xFF << field)) >> field;
	}
	return 0;
}