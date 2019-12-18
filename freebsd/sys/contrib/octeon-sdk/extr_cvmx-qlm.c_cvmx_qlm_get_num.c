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
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CNF71XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 

int cvmx_qlm_get_num(void)
{
    if (OCTEON_IS_MODEL(OCTEON_CN68XX))
        return 5;
    else if (OCTEON_IS_MODEL(OCTEON_CN66XX))
        return 3;
    else if (OCTEON_IS_MODEL(OCTEON_CN63XX))
        return 3;
    else if (OCTEON_IS_MODEL(OCTEON_CN61XX))
        return 3;
    else if (OCTEON_IS_MODEL(OCTEON_CN56XX))
        return 4;
    else if (OCTEON_IS_MODEL(OCTEON_CN52XX) || OCTEON_IS_MODEL(OCTEON_CNF71XX))
        return 2;

    //cvmx_dprintf("Warning: cvmx_qlm_get_num: This chip does not have QLMs\n");
    return 0;
}