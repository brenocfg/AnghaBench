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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_PFC0 ; 
 int /*<<< orphan*/  CVMX_L2C_PFC1 ; 
 int /*<<< orphan*/  CVMX_L2C_PFC2 ; 
 int /*<<< orphan*/  CVMX_L2C_PFC3 ; 
 int CVMX_L2C_TADS ; 
 int /*<<< orphan*/  CVMX_L2C_TADX_PFC0 (int) ; 
 int /*<<< orphan*/  CVMX_L2C_TADX_PFC1 (int) ; 
 int /*<<< orphan*/  CVMX_L2C_TADX_PFC2 (int) ; 
 int /*<<< orphan*/  CVMX_L2C_TADX_PFC3 (int) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

uint64_t cvmx_l2c_read_perf(uint32_t counter)
{
	switch (counter) {
	case 0:
		if (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			return cvmx_read_csr(CVMX_L2C_PFC0);
		else {
			uint64_t counter = 0;
			int tad;

			for (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_read_csr(CVMX_L2C_TADX_PFC0(tad));
			return counter;
		}
	case 1:
		if (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			return cvmx_read_csr(CVMX_L2C_PFC1);
		else {
			uint64_t counter = 0;
			int tad;

			for (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_read_csr(CVMX_L2C_TADX_PFC1(tad));
			return counter;
		}
	case 2:
		if (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			return cvmx_read_csr(CVMX_L2C_PFC2);
		else {
			uint64_t counter = 0;
			int tad;

			for (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_read_csr(CVMX_L2C_TADX_PFC2(tad));
			return counter;
		}
	case 3:
	default:
		if (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			return cvmx_read_csr(CVMX_L2C_PFC3);
		else {
			uint64_t counter = 0;
			int tad;

			for (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_read_csr(CVMX_L2C_TADX_PFC3(tad));
			return counter;
		}
	}
}