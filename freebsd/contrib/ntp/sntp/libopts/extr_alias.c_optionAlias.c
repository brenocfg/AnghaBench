#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ optCt; TYPE_3__* pOptDesc; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_11__ {int /*<<< orphan*/  argString; } ;
struct TYPE_13__ {int fOptState; scalar_t__ optOccCt; scalar_t__ optMaxCt; int /*<<< orphan*/  (* pOptProc ) (TYPE_2__*,TYPE_3__*) ;TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 TYPE_2__* OPTPROC_EMIT_LIMIT ; 
 int OPTST_DEFINED ; 
 int OPTST_PERSISTENT_MASK ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_3__*) ; 
 int too_many_occurrences (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zbad_alias_id ; 

int
optionAlias(tOptions * opts, tOptDesc * old_od, unsigned int alias)
{
    tOptDesc * new_od;

    if (opts <= OPTPROC_EMIT_LIMIT)
        return 0;

    new_od = opts->pOptDesc + alias;
    if ((unsigned)opts->optCt <= alias) {
        fputs(zbad_alias_id, stderr);
        option_exits(EXIT_FAILURE);
    }

    /*
     *  Copy over the option instance flags
     */
    new_od->fOptState &= OPTST_PERSISTENT_MASK;
    new_od->fOptState |= (old_od->fOptState & ~OPTST_PERSISTENT_MASK);
    new_od->optArg.argString = old_od->optArg.argString;

    /*
     *  Keep track of count only for DEFINED (command line) options.
     *  IF we have too many, build up an error message and bail.
     */
    if (  (new_od->fOptState & OPTST_DEFINED)
       && (++new_od->optOccCt > new_od->optMaxCt)  )
        return too_many_occurrences(opts, new_od);

    /*
     *  Clear the state bits and counters
     */
    old_od->fOptState &= OPTST_PERSISTENT_MASK;
    old_od->optOccCt   = 0;

    /*
     *  If there is a procedure to call, call it
     */
    if (new_od->pOptProc != NULL)
        (*new_od->pOptProc)(opts, new_od);
    return 0;
}