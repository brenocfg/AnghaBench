#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint128_t ;
struct TYPE_8__ {int /*<<< orphan*/  sign; int /*<<< orphan*/  exp; scalar_t__ signif; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 TYPE_1__ F80_NAN ; 
 int /*<<< orphan*/  f80_is_supported (TYPE_1__) ; 
 scalar_t__ f80_isnan (TYPE_1__) ; 
 TYPE_1__ u128_normalize_round (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unbias (int /*<<< orphan*/ ) ; 

float80 f80_scale(float80 x, int scale) {
    if (!f80_is_supported(x) || f80_isnan(x))
        return F80_NAN;
    return u128_normalize_round((uint128_t) x.signif << 64, unbias(x.exp) + scale, x.sign);
}