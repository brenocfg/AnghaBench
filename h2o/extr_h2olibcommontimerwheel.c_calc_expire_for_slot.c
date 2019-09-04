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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t H2O_TIMERWHEEL_BITS_PER_WHEEL ; 
 size_t UINT64_MAX ; 

__attribute__((used)) static void calc_expire_for_slot(size_t num_wheels, uint64_t last_run, size_t wheel, size_t slot, uint64_t *at_min,
                                 uint64_t *at_max)
{
#define SPAN(i) ((uint64_t)1 << (H2O_TIMERWHEEL_BITS_PER_WHEEL * (i))) /* returns the span of time for given wheel index */

    int adj_at_min = 0;

    *at_min = (last_run & ~(SPAN(wheel + 1) - 1)) + slot * SPAN(wheel);

    if (wheel == 0) {
        if (*at_min < last_run)
            adj_at_min = 1;
    } else {
        if (*at_min <= last_run)
            adj_at_min = 1;
    }
    if (adj_at_min)
        *at_min += SPAN(wheel + 1);

    if (wheel == num_wheels - 1) {
        *at_max = UINT64_MAX;
    } else {
        *at_max = *at_min + SPAN(wheel) - 1;
    }

#undef SPAN
}