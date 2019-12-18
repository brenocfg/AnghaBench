#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int exp; int /*<<< orphan*/  sign; int /*<<< orphan*/  signif; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */
 int /*<<< orphan*/  u128_shift_right_round (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float80 f80_shift_right(float80 f, int shift) {
    f.signif = u128_shift_right_round(f.signif, shift, f.sign);
    f.exp += shift;
    return f;
}