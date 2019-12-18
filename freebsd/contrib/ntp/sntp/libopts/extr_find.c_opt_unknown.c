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
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_8__ {scalar_t__ default_opt; } ;
struct TYPE_9__ {scalar_t__ pOptDesc; int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgPath; TYPE_1__ specOptIdx; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_10__ {scalar_t__ pOD; char const* pzOptArg; int /*<<< orphan*/  optType; } ;
typedef  TYPE_3__ tOptState ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ NAMED_OPTS (TYPE_2__*) ; 
 scalar_t__ NO_EQUIVALENT ; 
 int OPTPROC_ERRSTOP ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  TOPT_DEFAULT ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* zIllOptStr ; 

__attribute__((used)) static tSuccess
opt_unknown(tOptions * opts, char const * name, char * arg, tOptState * st)
{
    /*
     *  IF there is no equal sign
     *     *AND* we are using named arguments
     *     *AND* there is a default named option,
     *  THEN return that option.
     */
    if (  (arg == NULL)
       && NAMED_OPTS(opts)
       && (opts->specOptIdx.default_opt != NO_EQUIVALENT)) {

        st->pOD      = opts->pOptDesc + opts->specOptIdx.default_opt;
        st->pzOptArg = name;
        st->optType  = TOPT_DEFAULT;
        return SUCCESS;
    }

    if ((opts->fOptSet & OPTPROC_ERRSTOP) != 0) {
        fprintf(stderr, zIllOptStr, opts->pzProgPath, name);
        (*opts->pUsageProc)(opts, EXIT_FAILURE);
        /* NOTREACHED */
        _exit(EXIT_FAILURE); /* to be certain */
    }

    return FAILURE;
}