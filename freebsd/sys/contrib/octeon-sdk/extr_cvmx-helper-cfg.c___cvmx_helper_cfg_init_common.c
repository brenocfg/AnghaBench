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
 int octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cvmx_helper_cfg_init_common(void)
{
    int val;

#ifndef CVMX_ENABLE_HELPER_FUNCTIONS
    val = 0;
#else
    val = (octeon_has_feature(OCTEON_FEATURE_PKND));
#endif

    return val;
}