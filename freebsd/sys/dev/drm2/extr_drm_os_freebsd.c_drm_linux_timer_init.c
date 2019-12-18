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
 unsigned long drm_linux_timer_hz_mask ; 
 scalar_t__ hz ; 

__attribute__((used)) static void
drm_linux_timer_init(void *arg)
{

        /*
         * Compute an internal HZ value which can divide 2**32 to
         * avoid timer rounding problems when the tick value wraps
         * around 2**32:
         */
        drm_linux_timer_hz_mask = 1;
        while (drm_linux_timer_hz_mask < (unsigned long)hz)
                drm_linux_timer_hz_mask *= 2;
        drm_linux_timer_hz_mask--;
}