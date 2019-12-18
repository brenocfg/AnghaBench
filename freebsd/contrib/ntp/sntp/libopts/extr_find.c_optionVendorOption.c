#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_18__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ tOptState ;
struct TYPE_16__ {char* argString; } ;
struct TYPE_19__ {int fOptState; TYPE_1__ optArg; } ;
typedef  TYPE_4__ tOptDesc ;

/* Variables and functions */
 scalar_t__ DO_IMMEDIATELY (int /*<<< orphan*/ ) ; 
 scalar_t__ DO_NORMALLY (int /*<<< orphan*/ ) ; 
 scalar_t__ DO_SECOND_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 TYPE_2__* OPTPROC_EMIT_LIMIT ; 
 int OPTPROC_IMMEDIATE ; 
 int OPTPROC_VENDOR_OPT ; 
 TYPE_3__ OPTSTATE_INITIALIZER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPTST_DEFINED ; 
 int OPTST_RESET ; 
 int /*<<< orphan*/  PRESET ; 
 int /*<<< orphan*/  SUCCESSFUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_opt_arg (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  handle_opt (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  opt_find_long (TYPE_2__*,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* zIllVendOptStr ; 

void
optionVendorOption(tOptions * pOpts, tOptDesc * pOD)
{
    tOptState     opt_st   = OPTSTATE_INITIALIZER(PRESET);
    char const *  vopt_str = pOD->optArg.argString;

    if (pOpts <= OPTPROC_EMIT_LIMIT)
        return;

    if ((pOD->fOptState & OPTST_RESET) != 0)
        return;

    if ((pOD->fOptState & OPTPROC_IMMEDIATE) == 0)
        opt_st.flags = OPTST_DEFINED;

    if (  ((pOpts->fOptSet & OPTPROC_VENDOR_OPT) == 0)
       || ! SUCCESSFUL(opt_find_long(pOpts, vopt_str, &opt_st))
       || ! SUCCESSFUL(get_opt_arg(pOpts, &opt_st)) )
    {
        fprintf(stderr, zIllVendOptStr, pOpts->pzProgName, vopt_str);
        (*pOpts->pUsageProc)(pOpts, EXIT_FAILURE);
        /* NOTREACHED */
        _exit(EXIT_FAILURE); /* to be certain */
    }

    /*
     *  See if we are in immediate handling state.
     */
    if (pOpts->fOptSet & OPTPROC_IMMEDIATE) {
        /*
         *  See if the enclosed option is okay with that state.
         */
        if (DO_IMMEDIATELY(opt_st.flags))
            (void)handle_opt(pOpts, &opt_st);

    } else {
        /*
         *  non-immediate direction.
         *  See if the enclosed option is okay with that state.
         */
        if (DO_NORMALLY(opt_st.flags) || DO_SECOND_TIME(opt_st.flags))
            (void)handle_opt(pOpts, &opt_st);
    }
}