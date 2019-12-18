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
struct TYPE_5__ {scalar_t__ lo; scalar_t__ hi; } ;
typedef  scalar_t__ FICL_UNS ;
typedef  TYPE_1__ DPUNS ;

/* Variables and functions */
 TYPE_1__ ficlLongMul (scalar_t__,scalar_t__) ; 

DPUNS m64Mac(DPUNS u, FICL_UNS mul, FICL_UNS add)
{
    DPUNS resultLo = ficlLongMul(u.lo, mul);
    DPUNS resultHi = ficlLongMul(u.hi, mul);
    resultLo.hi += resultHi.lo;
    resultHi.lo = resultLo.lo + add;

    if (resultHi.lo < resultLo.lo)
        resultLo.hi++;

    resultLo.lo = resultHi.lo;

    return resultLo;
}