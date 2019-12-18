#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {TYPE_1__* p_FmStateStruct; } ;
typedef  TYPE_2__ t_Fm ;
struct TYPE_3__ {int /*<<< orphan*/  fmClkFreq; } ;

/* Variables and functions */

uint16_t FmGetClockFreq(t_Handle h_Fm)
{
    t_Fm *p_Fm = (t_Fm*)h_Fm;

    /* for multicore environment: this depends on the
     * fact that fmClkFreq was properly initialized at "init". */
    return p_Fm->p_FmStateStruct->fmClkFreq;
}