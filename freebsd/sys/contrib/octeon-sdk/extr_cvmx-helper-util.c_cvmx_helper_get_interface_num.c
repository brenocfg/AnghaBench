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
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

int cvmx_helper_get_interface_num(int ipd_port)
{
    if (octeon_has_feature(OCTEON_FEATURE_PKND))
    {
        if (ipd_port >= 0x800 && ipd_port < 0x900)
            return 0;
        else if (ipd_port >= 0x900 && ipd_port < 0xa00)
            return 1;
        else if (ipd_port >= 0xa00 && ipd_port < 0xb00)
            return 2;
        else if (ipd_port >= 0xb00 && ipd_port < 0xc00)
            return 3;
        else if (ipd_port >= 0xc00 && ipd_port < 0xd00)
            return 4;
        else if (ipd_port >= 0x400 && ipd_port < 0x500)
            return 5;
        else if (ipd_port >= 0x500 && ipd_port < 0x600)
            return 6;
        else if (ipd_port >= 0x100 && ipd_port < 0x120)
            return 7;
        else if (ipd_port < 8)
            return 8;
    } else {
	if (ipd_port < 16)
	    return 0;
	else if (ipd_port < 32)
	    return 1;
	else if (ipd_port < 36)
	    return 2;
	else if (ipd_port < 40)
	    return 3;
	else if (ipd_port < 42)
	    return 4;
	else if (ipd_port < 44)
	    return 5;
	else if (ipd_port < 46)
	    return 6;
    }
    cvmx_dprintf("cvmx_helper_get_interface_num: Illegal IPD port number %d\n", ipd_port);
    return -1;
}