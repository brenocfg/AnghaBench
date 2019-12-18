#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ signif; scalar_t__ exp; scalar_t__ sign; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 TYPE_1__ F80_NAN ; 
 TYPE_1__ f80_add (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ f80_div (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ f80_from_int (int) ; 
 scalar_t__ f80_gt (TYPE_1__,TYPE_1__) ; 
 scalar_t__ f80_isnan (TYPE_1__) ; 
 scalar_t__ f80_lt (TYPE_1__,TYPE_1__) ; 
 scalar_t__ f80_lte (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ f80_mul (TYPE_1__,TYPE_1__) ; 

float80 f80_log2(float80 x) {
    float80 zero = f80_from_int(0);
    float80 one = f80_from_int(1);
    float80 two = f80_from_int(2);
    if (f80_isnan(x) || f80_lte(x, zero))
        return F80_NAN;

    int ipart = 0;
    while (f80_lt(x, one)) {
        ipart--;
        x = f80_mul(x, two);
    }
    while (f80_gt(x, two)) {
        ipart++;
        x = f80_div(x, two);
    }
    float80 res = f80_from_int(ipart);

    float80 bit = one;
    while (f80_gt(bit, zero)) {
        while (f80_lte(x, two) && f80_gt(bit, zero)) {
            x = f80_mul(x, x);
            bit = f80_div(bit, two);
        }
        float80 oldres = res;
        res = f80_add(res, bit);
        if (oldres.signif == res.signif && oldres.exp == res.exp && oldres.sign == res.sign)
            break;
        x = f80_div(x, two);
    }
    return res;
}