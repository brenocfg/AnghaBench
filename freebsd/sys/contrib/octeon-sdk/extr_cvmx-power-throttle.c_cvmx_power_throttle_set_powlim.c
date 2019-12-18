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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PTH_INDEX_HRMPOWADJ ; 
 int /*<<< orphan*/  CVMX_PTH_INDEX_MAXPOW ; 
 int /*<<< orphan*/  CVMX_PTH_INDEX_POWLIM ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cvmx_power_throttle_csr_addr (int) ; 
 scalar_t__ cvmx_power_throttle_get_field (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_power_throttle_set_field (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint64_t cvmx_power_throttle_set_powlim(int ppid,
    uint8_t percentage)
{
    if (OCTEON_IS_MODEL(OCTEON_CN6XXX))
    {
        uint64_t t, csr_addr, r;

        assert(percentage < 101);
        csr_addr = cvmx_power_throttle_csr_addr(ppid);
        r = cvmx_read_csr(csr_addr);

        t = cvmx_power_throttle_get_field(r, CVMX_PTH_INDEX_MAXPOW);
	if (!OCTEON_IS_MODEL(OCTEON_CN63XX))
	{
	    uint64_t s;

	    s = cvmx_power_throttle_get_field(r, CVMX_PTH_INDEX_HRMPOWADJ);
	    assert(t > s);
	    t = t - s;
	}

	t = percentage * t / 100;
        r = cvmx_power_throttle_set_field(CVMX_PTH_INDEX_POWLIM, r, t);

        cvmx_write_csr(csr_addr, r);
        return r;
    }
    return 0;
}