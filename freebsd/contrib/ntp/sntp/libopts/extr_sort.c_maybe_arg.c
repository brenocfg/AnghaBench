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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_5__ {size_t curOptIdx; size_t origArgCt; char** origArgVect; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {int optType; int /*<<< orphan*/ * pzOptArg; } ;
typedef  TYPE_2__ tOptState ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 char NUL ; 
 int /*<<< orphan*/  PROBLEM ; 
 int /*<<< orphan*/  SUCCESS ; 
#define  TOPT_LONG 129 
#define  TOPT_SHORT 128 

__attribute__((used)) static tSuccess
maybe_arg(tOptions * opts, char * arg_txt, tOptState * pOS,
          char ** opt_txt, uint32_t * opt_idx)
{
    /*
     *  An option argument is optional.
     */
    switch (pOS->optType) {
    case TOPT_SHORT:
        /*
         *  IF nothing is glued on after the current flag character,
         *  THEN see if there is another argument.  If so and if it
         *  does *NOT* start with a hyphen, then it is the option arg.
         */
        if (*arg_txt != NUL)
            return SUCCESS;
        break;

    case TOPT_LONG:
        /*
         *  Look for an argument if we don't already have one (glued on
         *  with a `=' character)
         */
        if (pOS->pzOptArg != NULL)
            return SUCCESS;
        break;

    default:
        return FAILURE;
    }
    if (opts->curOptIdx >= opts->origArgCt)
        return PROBLEM;

    arg_txt = opts->origArgVect[ opts->curOptIdx ];
    if (*arg_txt != '-')
        opt_txt[ (*opt_idx)++ ] = opts->origArgVect[ (opts->curOptIdx)++ ];
    return SUCCESS;
}