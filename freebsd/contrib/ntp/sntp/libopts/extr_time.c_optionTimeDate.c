#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_13__ {int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgName; int /*<<< orphan*/ * pzPkgDataDir; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_12__ {scalar_t__ argInt; int /*<<< orphan*/  argString; } ;
struct TYPE_14__ {int fOptState; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 char* AGALOC (scalar_t__,char const*) ; 
 int /*<<< orphan*/  AGFREE (int /*<<< orphan*/ ) ; 
 scalar_t__ BAD_TIME ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  HAS_pzPkgDataDir (TYPE_2__*) ; 
 scalar_t__ INQUERY_CALL (TYPE_2__*,TYPE_3__*) ; 
 int OPTPROC_ERRSTOP ; 
 int OPTST_ALLOC_ARG ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getdate_r (int /*<<< orphan*/ ,struct tm*) ; 
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/  optionTimeVal (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 char* zNotDate ; 

void
optionTimeDate(tOptions * opts, tOptDesc * od)
{
#if defined(HAVE_GETDATE_R) && defined(HAVE_PUTENV)
    if (INQUERY_CALL(opts, od))
        return;

    if ((! HAS_pzPkgDataDir(opts)) || (opts->pzPkgDataDir == NULL))
        goto default_action;

    /*
     *  Export the DATEMSK environment variable.  getdate_r() uses it to
     *  find the file with the strptime formats.  If we cannot find the file
     *  we need ($PKGDATADIR/datemsk), then fall back to just a time duration.
     */
    {
        static char * envptr = NULL;

        if (envptr == NULL) {
            static char const fmt[] = "DATEMSK=%s/datemsk";
            envptr = AGALOC(sizeof(fmt) + strlen(opts->pzPkgDataDir), fmt);
            sprintf(envptr, fmt, opts->pzPkgDataDir);

            putenv(envptr);
        }

        if (access(envptr+8, R_OK) != 0)
            goto default_action;
    }

    /*
     *  Convert the date to a time since the epoch and stash it in a long int.
     */
    {
        struct tm stm;
        time_t tm;

        if (getdate_r(od->optArg.argString, &stm) != 0) {
            fprintf(stderr, zNotDate, opts->pzProgName,
                    od->optArg.argString);
            if ((opts->fOptSet & OPTPROC_ERRSTOP) != 0)
                (*(opts->pUsageProc))(opts, EXIT_FAILURE);
            return;
        }

        tm = mktime(&stm);

        if (od->fOptState & OPTST_ALLOC_ARG) {
            AGFREE(od->optArg.argString);
            od->fOptState &= ~OPTST_ALLOC_ARG;
        }

        od->optArg.argInt = tm;
    }
    return;

 default_action:

#endif
    optionTimeVal(opts, od);
    if (od->optArg.argInt != BAD_TIME)
        od->optArg.argInt += (long)time(NULL);
}