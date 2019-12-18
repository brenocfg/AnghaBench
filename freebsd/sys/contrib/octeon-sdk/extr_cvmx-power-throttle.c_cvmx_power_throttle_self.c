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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PTH_AVAILABLE ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 scalar_t__ cvmx_power_throttle_set_powlim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cvmx_power_throttle_self(uint8_t percentage)
{
    if (!CVMX_PTH_AVAILABLE)
        return -1;

    if (cvmx_power_throttle_set_powlim(cvmx_get_core_num(),
        percentage) == 0)
	return -1;

    return 0;
}