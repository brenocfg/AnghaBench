#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint128_t ;
struct TYPE_12__ {int sign; int signif; int /*<<< orphan*/  exp; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 TYPE_1__ F80_INF ; 
 TYPE_1__ F80_NAN ; 
 int /*<<< orphan*/  f80_is_supported (TYPE_1__) ; 
 scalar_t__ f80_isinf (TYPE_1__) ; 
 scalar_t__ f80_isnan (TYPE_1__) ; 
 scalar_t__ f80_iszero (TYPE_1__) ; 
 TYPE_1__ u128_normalize_round (int,int,int) ; 
 int unbias_denormal (int /*<<< orphan*/ ) ; 

float80 f80_mul(float80 a, float80 b) {
    if (!f80_is_supported(a) || !f80_is_supported(b))
        return F80_NAN;
    if (f80_isnan(a))
        return F80_NAN;
    if (f80_isnan(b))
        return F80_NAN;

    if (f80_isinf(a) || f80_isinf(b)) {
        // infinity times zero is undefined
        if (f80_iszero(a) || f80_iszero(b))
            return F80_NAN;
        // infinity times anything else is infinity
        float80 f = F80_INF;
        f.sign = a.sign ^ b.sign;
        return f;
    }

    // add exponents (the +1 is necessary to be correct in 128-bit precision)
    int f_exp = unbias_denormal(a.exp) + unbias_denormal(b.exp) + 1;
    // multiply significands
    uint128_t f_signif = (uint128_t) a.signif * b.signif;
    // normalize and round the 128-bit result
    float80 f = u128_normalize_round(f_signif, f_exp, a.sign ^ b.sign);
    // xor signs
    f.sign = a.sign ^ b.sign;
    return f;
}