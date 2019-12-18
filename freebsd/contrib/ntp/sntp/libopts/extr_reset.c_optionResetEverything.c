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
struct TYPE_4__ {int presetOptCt; int /*<<< orphan*/ * pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
typedef  int /*<<< orphan*/  tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  optionReset (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
optionResetEverything(tOptions * pOpts)
{
    tOptDesc * pOD = pOpts->pOptDesc;
    int        ct  = pOpts->presetOptCt;

    for (;;) {
        optionReset(pOpts, pOD);

        if (--ct <= 0)
            break;
        pOD++;
    }
}