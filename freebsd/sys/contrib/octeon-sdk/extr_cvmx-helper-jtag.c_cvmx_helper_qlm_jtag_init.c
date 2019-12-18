#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int clk_div; int bypass; int bypass_ext; scalar_t__ mux_sel; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_ciu_qlm_jtgc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_QLM_JTGC ; 
 int /*<<< orphan*/  CVMX_CLOCK_SCLK ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void cvmx_helper_qlm_jtag_init(void)
{
    cvmx_ciu_qlm_jtgc_t jtgc;
    int clock_div = 0;
    int divisor;

    divisor = cvmx_clock_get_rate(CVMX_CLOCK_SCLK) / (1000000 *
        (OCTEON_IS_MODEL(OCTEON_CN68XX) ? 10 : 25));

    divisor = (divisor-1)>>2;
    /* Convert the divisor into a power of 2 shift */
    while (divisor)
    {
        clock_div++;
        divisor>>=1;
    }

    /* Clock divider for QLM JTAG operations.  sclk is divided by 2^(CLK_DIV + 2) */
    jtgc.u64 = 0;
    jtgc.s.clk_div = clock_div;
    jtgc.s.mux_sel = 0;
    if (OCTEON_IS_MODEL(OCTEON_CN52XX))
        jtgc.s.bypass = 0x3;
    else if (OCTEON_IS_MODEL(OCTEON_CN63XX) || OCTEON_IS_MODEL(OCTEON_CN66XX))
        jtgc.s.bypass = 0x7;
    else
        jtgc.s.bypass = 0xf;
    if (OCTEON_IS_MODEL(OCTEON_CN68XX))
        jtgc.s.bypass_ext = 1;
    cvmx_write_csr(CVMX_CIU_QLM_JTGC, jtgc.u64);
    cvmx_read_csr(CVMX_CIU_QLM_JTGC);
}