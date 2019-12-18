#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tOptions ;
struct TYPE_8__ {int /*<<< orphan*/ * argString; } ;
struct TYPE_9__ {int fOptState; TYPE_3__* optCookie; TYPE_1__ optArg; } ;
typedef  TYPE_2__ tOptDesc ;
struct TYPE_10__ {int useCt; struct TYPE_10__** apzArgs; } ;
typedef  TYPE_3__ tArgList ;

/* Variables and functions */
 int /*<<< orphan*/  AGDUPSTR (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AGFREE (TYPE_3__*) ; 
 scalar_t__ INQUERY_CALL (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int OPTST_RESET ; 
 int /*<<< orphan*/  VOIDP (char*) ; 
 int /*<<< orphan*/  addArgListEntry (TYPE_3__**,int /*<<< orphan*/ ) ; 

void
optionStackArg(tOptions * opts, tOptDesc * od)
{
    char * pz;

    if (INQUERY_CALL(opts, od))
        return;

    if ((od->fOptState & OPTST_RESET) != 0) {
        tArgList * arg_list = od->optCookie;
        int ix;
        if (arg_list == NULL)
            return;

        ix = arg_list->useCt;
        while (--ix >= 0)
            AGFREE(arg_list->apzArgs[ix]);
        AGFREE(arg_list);

    } else {
        if (od->optArg.argString == NULL)
            return;

        AGDUPSTR(pz, od->optArg.argString, "stack arg");
        addArgListEntry(&(od->optCookie), VOIDP(pz));
    }
}