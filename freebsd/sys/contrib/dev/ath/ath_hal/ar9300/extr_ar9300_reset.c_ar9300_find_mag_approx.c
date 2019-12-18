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
struct ath_hal {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__) ; 

__attribute__((used)) static int32_t
ar9300_find_mag_approx(struct ath_hal *ah, int32_t in_re, int32_t in_im)
{
    int32_t abs_i = abs(in_re);
    int32_t abs_q = abs(in_im);
    int32_t max_abs, min_abs;

    if (abs_i > abs_q) {
        max_abs = abs_i;
        min_abs = abs_q;
    } else {
        max_abs = abs_q;
        min_abs = abs_i; 
    }

    return (max_abs - (max_abs / 32) + (min_abs / 8) + (min_abs / 4));
}