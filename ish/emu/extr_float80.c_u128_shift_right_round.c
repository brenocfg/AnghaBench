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
typedef  int uint64_t ;
typedef  int uint128_t ;

/* Variables and functions */
 int f80_rounding_mode ; 
#define  round_down 130 
#define  round_to_nearest 129 
#define  round_up 128 

__attribute__((used)) static uint128_t u128_shift_right_round(uint128_t i, int shift, int sign) {
    // we're going to be shifting stuff by shift - 1, so stay safe
    if (shift == 0)
        return i;
    if (shift > 127)
        return 0;

    // stuff necessary for rounding to nearest or even. reference: https://stackoverflow.com/a/8984135
    // grab the guard bit, the last bit shifted out
    int guard = (i >> (shift - 1)) & 1;
    // now grab the rest of the bits being shifted out
    uint64_t rest = i & ~(-1ul << (shift - 1));

    i >>= shift;
    switch (f80_rounding_mode) {
        case round_up:
            if (!sign)
                i++;
            break;
        case round_down:
            if (sign)
                i++;
            break;
        case round_to_nearest:
            // if guard bit is not set, no need to round up
            if (guard) {
                if (rest != 0)
                    i++; // round up
                else if (i & 1)
                    i++; // round to nearest even
            }
            break;
    }
    return i;
}