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
struct TYPE_5__ {int /*<<< orphan*/  pzPROGNAME; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {int optMaxCt; int fOptState; int /*<<< orphan*/ * pz_NAME; int /*<<< orphan*/ * pOptProc; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 char* CHK_MAX_COUNT ; 
 char* ECHO_N_EXIT ; 
 int /*<<< orphan*/  LONG_USE_STR ; 
 char* LVL3_CMD ; 
 char* MULTI_ARG_FMT ; 
 unsigned int NOLIMIT ; 
 int /*<<< orphan*/  NO_ARG_NEEDED ; 
 int /*<<< orphan*/  NO_LOAD_WARN ; 
 int /*<<< orphan*/  NO_SAVE_OPTS ; 
 int /*<<< orphan*/  OK_NEED_OPT_ARG ; 
 scalar_t__ OPARG_TYPE_NONE ; 
 int OPTST_ARG_OPTIONAL ; 
 scalar_t__ OPTST_GET_ARGTYPE (int) ; 
 char* PAGE_USAGE_TEXT ; 
 char* SET_MULTI_ARG ; 
 char* SGL_ARG_FMT ; 
 int /*<<< orphan*/  VER_STR ; 
 int /*<<< orphan*/  YES_NEED_OPT_ARG ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * optionLoadOpt ; 
 int /*<<< orphan*/ * optionPagedUsage ; 
 int /*<<< orphan*/ * optionPrintVersion ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  zOptionEndSelect ; 

__attribute__((used)) static void
emit_action(tOptions * opts, tOptDesc * od)
{
    if (od->pOptProc == optionPrintVersion)
        printf(ECHO_N_EXIT, opts->pzPROGNAME, VER_STR);

    else if (od->pOptProc == optionPagedUsage)
        printf(PAGE_USAGE_TEXT, opts->pzPROGNAME);

    else if (od->pOptProc == optionLoadOpt) {
        printf(LVL3_CMD, NO_LOAD_WARN);
        printf(LVL3_CMD, YES_NEED_OPT_ARG);

    } else if (od->pz_NAME == NULL) {

        if (od->pOptProc == NULL) {
            printf(LVL3_CMD, NO_SAVE_OPTS);
            printf(LVL3_CMD, OK_NEED_OPT_ARG);
        } else
            printf(ECHO_N_EXIT, opts->pzPROGNAME, LONG_USE_STR);

    } else {
        if (od->optMaxCt == 1)
            printf(SGL_ARG_FMT, opts->pzPROGNAME, od->pz_NAME);
        else {
            if ((unsigned)od->optMaxCt < NOLIMIT)
                printf(CHK_MAX_COUNT, opts->pzPROGNAME,
                       od->pz_NAME, od->optMaxCt);

            printf(MULTI_ARG_FMT, opts->pzPROGNAME, od->pz_NAME);
        }

        /*
         *  Fix up the args.
         */
        if (OPTST_GET_ARGTYPE(od->fOptState) == OPARG_TYPE_NONE) {
            printf(SET_MULTI_ARG, opts->pzPROGNAME, od->pz_NAME);
            printf(LVL3_CMD, NO_ARG_NEEDED);

        } else if (od->fOptState & OPTST_ARG_OPTIONAL) {
            printf(SET_MULTI_ARG,  opts->pzPROGNAME, od->pz_NAME);
            printf(LVL3_CMD, OK_NEED_OPT_ARG);

        } else {
            printf(LVL3_CMD, YES_NEED_OPT_ARG);
        }
    }
    fputs(zOptionEndSelect, stdout);
}