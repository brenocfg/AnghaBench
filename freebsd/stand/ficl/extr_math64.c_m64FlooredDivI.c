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
typedef  int /*<<< orphan*/  UNSQR ;
struct TYPE_4__ {scalar_t__ rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_1__ INTQR ;
typedef  int /*<<< orphan*/  FICL_UNS ;
typedef  scalar_t__ FICL_INT ;
typedef  int /*<<< orphan*/  DPINT ;

/* Variables and functions */
 int /*<<< orphan*/  ficlLongDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64CastIU (int /*<<< orphan*/ ) ; 
 TYPE_1__ m64CastQRUI (int /*<<< orphan*/ ) ; 
 scalar_t__ m64IsNegative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m64Negate (int /*<<< orphan*/ ) ; 

INTQR m64FlooredDivI(DPINT num, FICL_INT den)
{
    INTQR qr;
    UNSQR uqr;
    int signRem = 1;
    int signQuot = 1;

    if (m64IsNegative(num))
    {
        num = m64Negate(num);
        signQuot = -signQuot;
    }

    if (den < 0)
    {
        den      = -den;
        signRem  = -signRem;
        signQuot = -signQuot;
    }

    uqr = ficlLongDiv(m64CastIU(num), (FICL_UNS)den);
    qr = m64CastQRUI(uqr);
    if (signQuot < 0)
    {
        qr.quot = -qr.quot;
        if (qr.rem != 0)
        {
            qr.quot--;
            qr.rem = den - qr.rem;
        }
    }

    if (signRem < 0)
        qr.rem = -qr.rem;

    return qr;
}