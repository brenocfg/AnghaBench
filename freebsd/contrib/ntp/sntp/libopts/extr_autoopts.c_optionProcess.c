#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int save_opts; } ;
struct TYPE_11__ {int curOptIdx; int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__ specOptIdx; int /*<<< orphan*/  pOptDesc; scalar_t__ origArgCt; int /*<<< orphan*/ * pzCurOpt; } ;
typedef  TYPE_2__ tOptions ;
typedef  int /*<<< orphan*/  tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
#define  NO_EQUIVALENT 128 
 int OPTPROC_ERRSTOP ; 
 int /*<<< orphan*/  SELECTED_OPT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCESSFUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_initialize (TYPE_2__*,int,char**) ; 
 int /*<<< orphan*/  is_consistent (TYPE_2__*) ; 
 int /*<<< orphan*/  optionSaveFile (TYPE_2__*) ; 
 int /*<<< orphan*/  option_exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regular_opts (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_struct (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  zbad_data_msg ; 

int
optionProcess(tOptions * opts, int a_ct, char ** a_v)
{
    if (! SUCCESSFUL(validate_struct(opts, a_v[0])))
        ao_bug(zbad_data_msg);
    
    /*
     *  Establish the real program name, the program full path,
     *  and do all the presetting the first time thru only.
     */
    if (! ao_initialize(opts, a_ct, a_v))
        return 0;

    /*
     *  IF we are (re)starting,
     *  THEN reset option location
     */
    if (opts->curOptIdx <= 0) {
        opts->curOptIdx = 1;
        opts->pzCurOpt  = NULL;
    }

    if (! SUCCESSFUL(regular_opts(opts)))
        return (int)opts->origArgCt;

    /*
     *  IF    there were no errors
     *    AND we have RC/INI files
     *    AND there is a request to save the files
     *  THEN do that now before testing for conflicts.
     *       (conflicts are ignored in preset options)
     */
    switch (opts->specOptIdx.save_opts) {
    case 0:
    case NO_EQUIVALENT:
        break;
    default:
    {
        tOptDesc * od = opts->pOptDesc + opts->specOptIdx.save_opts;

        if (SELECTED_OPT(od)) {
            optionSaveFile(opts);
            option_exits(EXIT_SUCCESS);
        }
    }
    }

    /*
     *  IF we are checking for errors,
     *  THEN look for too few occurrences of required options
     */
    if (((opts->fOptSet & OPTPROC_ERRSTOP) != 0)
       && (! is_consistent(opts)))
        (*opts->pUsageProc)(opts, EXIT_FAILURE);

    return (int)opts->curOptIdx;
}