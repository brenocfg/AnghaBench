#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tOptions ;
typedef  int /*<<< orphan*/  tOptionValue ;
struct TYPE_7__ {int /*<<< orphan*/  argString; } ;
struct TYPE_8__ {int fOptState; TYPE_3__* optCookie; int /*<<< orphan*/  pz_Name; TYPE_1__ optArg; } ;
typedef  TYPE_2__ tOptDesc ;
struct TYPE_9__ {int useCt; char** apzArgs; } ;
typedef  TYPE_3__ tArgList ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (TYPE_3__*) ; 
 int /*<<< orphan*/ * OPTPROC_EMIT_LIMIT ; 
 int OPTST_RESET ; 
 void* VOIDP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addArgListEntry (TYPE_3__**,void*) ; 
 int /*<<< orphan*/ * optionLoadNested (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optionUnloadNested (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
optionNestedVal(tOptions * opts, tOptDesc * od)
{
    if (opts < OPTPROC_EMIT_LIMIT)
        return;

    if (od->fOptState & OPTST_RESET) {
        tArgList *    arg_list = od->optCookie;
        int           ct;
        char const ** av;

        if (arg_list == NULL)
            return;
        ct = arg_list->useCt;
        av = arg_list->apzArgs;

        while (--ct >= 0) {
            void * p = VOIDP(*(av++));
            optionUnloadNested((tOptionValue const *)p);
        }

        AGFREE(od->optCookie);

    } else {
        tOptionValue * opt_val = optionLoadNested(
            od->optArg.argString, od->pz_Name, strlen(od->pz_Name));

        if (opt_val != NULL)
            addArgListEntry(&(od->optCookie), VOIDP(opt_val));
    }
}