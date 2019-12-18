#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* pUsageProc ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ tOptions ;
struct TYPE_9__ {int fOptState; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int OPTST_RESET ; 
#define  PAGER_STATE_CHILD 130 
#define  PAGER_STATE_INITIAL 129 
#define  PAGER_STATE_READY 128 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (void (*) ()) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_val (int /*<<< orphan*/ ) ; 
 char* mk_pager_cmd (char*) ; 
 int /*<<< orphan*/ * open_tmp_usage (char**) ; 
 int /*<<< orphan*/ * option_usage_fp ; 
 int pagerState ; 
 int print_exit ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system (char*) ; 

void
optionPagedUsage(tOptions * opts, tOptDesc * od)
{
#if ! defined(HAVE_WORKING_FORK)
    if ((od->fOptState & OPTST_RESET) != 0)
        return;

    (*opts->pUsageProc)(opts, EXIT_SUCCESS);
#else
    static bool sv_print_exit = false;
    static char * fil_name = NULL;

    /*
     *  IF we are being called after the usage proc is done
     *     (and thus has called "exit(2)")
     *  THEN invoke the pager to page through the usage file we created.
     */
    switch (pagerState) {
    case PAGER_STATE_INITIAL:
    {
        if ((od->fOptState & OPTST_RESET) != 0)
            return;
        option_usage_fp = open_tmp_usage(&fil_name);
        if (option_usage_fp == NULL)
            (*opts->pUsageProc)(opts, EXIT_SUCCESS);

        pagerState    = PAGER_STATE_READY;
        sv_print_exit = print_exit;

        /*
         *  Set up so this routine gets called during the exit logic
         */
        atexit((void(*)(void))optionPagedUsage);

        /*
         *  The usage procedure will now put the usage information into
         *  the temporary file we created above.  Keep any shell commands
         *  out of the result.
         */
        print_exit = false;
        (*opts->pUsageProc)(opts, EXIT_SUCCESS);

        /* NOTREACHED */
        _exit(EXIT_FAILURE);
    }

    case PAGER_STATE_READY:
        fil_name = mk_pager_cmd(fil_name);

        if (sv_print_exit) {
            fputs("\nexit 0\n", stdout);
            fclose(stdout);
            dup2(STDERR_FILENO, STDOUT_FILENO);

        } else {
            fclose(stderr);
            dup2(STDOUT_FILENO, STDERR_FILENO);
        }

        ignore_val( system( fil_name));
        AGFREE(fil_name);

    case PAGER_STATE_CHILD:
        /*
         *  This is a child process used in creating shell script usage.
         */
        break;
    }
#endif
}