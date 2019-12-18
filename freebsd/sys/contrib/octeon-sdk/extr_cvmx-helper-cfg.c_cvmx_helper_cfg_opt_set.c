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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t cvmx_helper_cfg_option_t ;

/* Variables and functions */
 size_t CVMX_HELPER_CFG_OPT_MAX ; 
 int /*<<< orphan*/ * cvmx_cfg_opts ; 

int cvmx_helper_cfg_opt_set(cvmx_helper_cfg_option_t opt, uint64_t val)
{
    if (opt >= CVMX_HELPER_CFG_OPT_MAX)
        return -1;
    
    cvmx_cfg_opts[opt] = val;

    return 0;
}