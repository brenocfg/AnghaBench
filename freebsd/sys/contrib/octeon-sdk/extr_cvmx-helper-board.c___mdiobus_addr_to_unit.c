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
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mdiobus_addr_to_unit(uint32_t addr)
{
    int unit = (addr >> 7) & 3;
    if (!OCTEON_IS_MODEL(OCTEON_CN68XX))
        unit >>= 1;
    return unit;
}