#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  argString; } ;
struct TYPE_7__ {int fOptState; TYPE_1__ optArg; scalar_t__ optCookie; } ;
typedef  TYPE_2__ tOptDesc ;
struct TYPE_8__ {int useCt; char** apzArgs; } ;
typedef  TYPE_3__ tArgList ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int OPTST_DISABLED ; 
 int OPTST_STACKED ; 
 int /*<<< orphan*/  prt_entry (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prt_str_arg(FILE * fp, tOptDesc * pOD)
{
    if (pOD->fOptState & OPTST_STACKED) {
        tArgList * pAL = (tArgList *)pOD->optCookie;
        int        uct = pAL->useCt;
        char const ** ppz = pAL->apzArgs;

        /*
         *  un-disable multiple copies of disabled options.
         */
        if (uct > 1)
            pOD->fOptState &= ~OPTST_DISABLED;

        while (uct-- > 0)
            prt_entry(fp, pOD, *(ppz++));
    } else {
        prt_entry(fp, pOD, pOD->optArg.argString);
    }
}