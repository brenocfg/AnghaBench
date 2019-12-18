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
typedef  int /*<<< orphan*/  __cvmx_qlm_jtag_field_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CNF71XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* __cvmx_qlm_jtag_field_cn52xx ; 
 int /*<<< orphan*/  const* __cvmx_qlm_jtag_field_cn56xx ; 
 int /*<<< orphan*/  const* __cvmx_qlm_jtag_field_cn63xx ; 
 int /*<<< orphan*/  const* __cvmx_qlm_jtag_field_cn66xx ; 
 int /*<<< orphan*/  const* __cvmx_qlm_jtag_field_cn68xx ; 

const __cvmx_qlm_jtag_field_t *cvmx_qlm_jtag_get_field(void)
{
    /* Figure out which JTAG chain description we're using */
    if (OCTEON_IS_MODEL(OCTEON_CN68XX))
        return __cvmx_qlm_jtag_field_cn68xx;
    else if (OCTEON_IS_MODEL(OCTEON_CN66XX) 
             || OCTEON_IS_MODEL(OCTEON_CN61XX)
             || OCTEON_IS_MODEL(OCTEON_CNF71XX))
        return __cvmx_qlm_jtag_field_cn66xx;
    else if (OCTEON_IS_MODEL(OCTEON_CN63XX))
        return __cvmx_qlm_jtag_field_cn63xx;
    else if (OCTEON_IS_MODEL(OCTEON_CN56XX))
        return __cvmx_qlm_jtag_field_cn56xx;
    else if (OCTEON_IS_MODEL(OCTEON_CN52XX))
        return __cvmx_qlm_jtag_field_cn52xx;
    else
    {
        //cvmx_dprintf("cvmx_qlm_jtag_get_field: Needs update for this chip\n");
        return NULL;
    }
}