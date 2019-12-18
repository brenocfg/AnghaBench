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
 int /*<<< orphan*/  OCTEON_CN63XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_CN63XX_PASS2_X ; 
 int /*<<< orphan*/  OCTEON_CN66XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_CN68XX_PASS1_X ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_qlm_jtag_set (int,int,char*,int) ; 

void __cvmx_qlm_pcie_idle_dac_tweak(void)
{
    int num_qlms = 0;
    int qlm;

    if (OCTEON_IS_MODEL(OCTEON_CN68XX_PASS1_X))
        num_qlms = 5;
    else if (OCTEON_IS_MODEL(OCTEON_CN66XX_PASS1_X))
        num_qlms = 3;
    else if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
             OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_X))
        num_qlms = 3;
    else
        return;

    /* Loop through the QLMs */
    for (qlm = 0; qlm < num_qlms; qlm++)
        cvmx_qlm_jtag_set(qlm, -1, "idle_dac", 0x2);
}