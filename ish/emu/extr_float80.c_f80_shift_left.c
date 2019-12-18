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
struct TYPE_4__ {int signif; int exp; } ;
typedef  TYPE_1__ float80 ;

/* Variables and functions */

__attribute__((used)) static float80 f80_shift_left(float80 f, int shift) {
    f.signif <<= shift;
    f.exp -= shift;
    return f;
}