#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int quot; int rem; } ;
typedef  TYPE_1__ UNSQR ;
struct TYPE_6__ {int hi; int lo; } ;
typedef  int FICL_UNS ;
typedef  TYPE_2__ DPUNS ;

/* Variables and functions */

UNSQR ficlLongDiv(DPUNS q, FICL_UNS y)
{
    UNSQR result;
    uint64_t qx, qh;

    qh = q.hi;
    qx = (qh << 32) | q.lo;

    result.quot = qx / y;
    result.rem  = qx % y;

    return result;
}