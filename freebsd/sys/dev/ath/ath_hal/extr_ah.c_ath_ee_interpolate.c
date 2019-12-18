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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */

int16_t
ath_ee_interpolate(uint16_t target, uint16_t srcLeft, uint16_t srcRight,
            int16_t targetLeft, int16_t targetRight)
{
    int16_t rv;

    if (srcRight == srcLeft) {
        rv = targetLeft;
    } else {
        rv = (int16_t)( ((target - srcLeft) * targetRight +
              (srcRight - target) * targetLeft) / (srcRight - srcLeft) );
    }
    return rv;
}