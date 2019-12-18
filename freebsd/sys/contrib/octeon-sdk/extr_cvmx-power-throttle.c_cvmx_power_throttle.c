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
typedef  int uint64_t ;

/* Variables and functions */
 int CVMX_MAX_CORES ; 
 int /*<<< orphan*/  CVMX_PTH_AVAILABLE ; 
 scalar_t__ cvmx_power_throttle_set_powlim (int,int /*<<< orphan*/ ) ; 

int cvmx_power_throttle(uint8_t percentage, uint64_t coremask)
{
    int ppid;
    int ret;

    if (!CVMX_PTH_AVAILABLE)
        return -1;

    ret = 0;
    for (ppid = 0; ppid < CVMX_MAX_CORES; ppid++)
    {
        if ((((uint64_t) 1) << ppid) & coremask)
	{
            if (cvmx_power_throttle_set_powlim(ppid, percentage) == 0)
	        ret = -2;
        }
    }

    return ret;
}