#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {scalar_t__ exp; int /*<<< orphan*/  signif; int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  INT64_MIN ; 
 scalar_t__ bias (int) ; 
 int /*<<< orphan*/  f80_is_supported (TYPE_1__) ; 
 TYPE_1__ f80_shift_right (TYPE_1__,scalar_t__) ; 

int64_t f80_to_int(float80 f) {
    if (!f80_is_supported(f))
        return INT64_MIN; // indefinite
    // if you need an exponent greater than 2^63 to represent this number, it
    // can't be represented as a 64-bit integer
    if (f.exp > bias(63))
        return !f.sign ? INT64_MAX : INT64_MIN;
    // shift right (reduce precision) until the exponent is 2^63
    f = f80_shift_right(f, bias(63) - f.exp);
    // and the answer should be the significand!
    return !f.sign ? f.signif : -f.signif;
}