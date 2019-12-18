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
 int /*<<< orphan*/  __cvmx_pow_display_v1 (void*,int) ; 
 int /*<<< orphan*/  __cvmx_pow_display_v2 (void*,int) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void cvmx_pow_display(void *buffer, int buffer_size)
{
    printf("POW Display Start\n");

    if (octeon_has_feature(OCTEON_FEATURE_PKND))
        __cvmx_pow_display_v2(buffer, buffer_size);
    else
        __cvmx_pow_display_v1(buffer, buffer_size);
        
    printf("POW Display End\n");
    return;
}