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
struct TYPE_4__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
typedef  TYPE_1__ DPINT ;

/* Variables and functions */

DPINT m64Negate(DPINT x)
{
    x.hi = ~x.hi;
    x.lo = ~x.lo;
    x.lo ++;
    if (x.lo == 0)
        x.hi++;

    return x;
}