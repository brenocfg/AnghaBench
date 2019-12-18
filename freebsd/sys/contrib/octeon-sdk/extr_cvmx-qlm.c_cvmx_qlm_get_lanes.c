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
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CNF71XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 

int cvmx_qlm_get_lanes(int qlm)
{
    if (OCTEON_IS_MODEL(OCTEON_CN61XX) && qlm == 1)
        return 2;
    else if (OCTEON_IS_MODEL(OCTEON_CNF71XX))
        return 2;
    
    return 4;
}