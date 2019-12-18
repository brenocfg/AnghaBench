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
typedef  int /*<<< orphan*/  FICL_INT ;
typedef  int /*<<< orphan*/  DPUNS ;
typedef  int /*<<< orphan*/  DPINT ;

/* Variables and functions */
 int /*<<< orphan*/  ficlLongMul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64CastUI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64Negate (int /*<<< orphan*/ ) ; 

DPINT m64MulI(FICL_INT x, FICL_INT y)
{
    DPUNS prod;
    int sign = 1;

    if (x < 0)
    {
        sign = -sign;
        x = -x;
    }

    if (y < 0)
    {
        sign = -sign;
        y = -y;
    }

    prod = ficlLongMul(x, y);
    if (sign > 0)
        return m64CastUI(prod);
    else
        return m64Negate(m64CastUI(prod));
}