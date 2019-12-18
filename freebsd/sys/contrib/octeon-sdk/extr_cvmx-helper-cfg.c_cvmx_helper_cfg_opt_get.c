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
 int /*<<< orphan*/  CVMX_HELPER_CFG_INVALID_VALUE ; 
 size_t CVMX_HELPER_CFG_OPT_MAX ; 
 int /*<<< orphan*/ * cvmx_cfg_opts ; 

uint64_t cvmx_helper_cfg_opt_get(cvmx_helper_cfg_option_t opt)
{
    if (opt >= CVMX_HELPER_CFG_OPT_MAX)
        return (uint64_t)CVMX_HELPER_CFG_INVALID_VALUE;

    return cvmx_cfg_opts[opt];
}