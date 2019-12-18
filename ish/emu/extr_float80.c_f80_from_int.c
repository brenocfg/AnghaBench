#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int sign; int /*<<< orphan*/  signif; scalar_t__ exp; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 scalar_t__ bias (int) ; 
 TYPE_1__ f80_normalize (TYPE_1__) ; 

float80 f80_from_int(int64_t i) {
    // stick i in the significand, give it an exponent of 2^63 to offset the
    // implicit binary point after the first bit, and then normalize
    float80 f = {
        .signif = i,
        .exp = bias(63),
        .sign = 0,
    };
    if (i == 0)
        f.exp = 0;
    if (i < 0) {
        f.sign = 1;
        f.signif = -i;
    }
    return f80_normalize(f);
}