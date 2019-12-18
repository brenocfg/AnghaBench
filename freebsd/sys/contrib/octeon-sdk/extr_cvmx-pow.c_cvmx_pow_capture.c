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
 int __cvmx_pow_capture_v1 (void*,int) ; 
 int __cvmx_pow_capture_v2 (void*,int) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

int cvmx_pow_capture(void *buffer, int buffer_size)
{
    if (octeon_has_feature(OCTEON_FEATURE_PKND))
        return __cvmx_pow_capture_v2(buffer, buffer_size);
    else
        return __cvmx_pow_capture_v1(buffer, buffer_size);
}