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
struct TYPE_5__ {scalar_t__ curOptIdx; scalar_t__ origArgCt; char** origArgVect; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {int optType; int /*<<< orphan*/ * pzOptArg; } ;
typedef  TYPE_2__ tOptState ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 char NUL ; 
 int /*<<< orphan*/  SUCCESS ; 
#define  TOPT_LONG 129 
#define  TOPT_SHORT 128 

__attribute__((used)) static tSuccess
must_arg(tOptions * opts, char * arg_txt, tOptState * pOS,
         char ** opt_txt, uint32_t * opt_idx)
{
    /*
     *  An option argument is required.  Long options can either have
     *  a separate command line argument, or an argument attached by
     *  the '=' character.  Figure out which.
     */
    switch (pOS->optType) {
    case TOPT_SHORT:
        /*
         *  See if an arg string follows the flag character.  If not,
         *  the next arg must be the option argument.
         */
        if (*arg_txt != NUL)
            return SUCCESS;
        break;

    case TOPT_LONG:
        /*
         *  See if an arg string has already been assigned (glued on
         *  with an `=' character).  If not, the next is the opt arg.
         */
        if (pOS->pzOptArg != NULL)
            return SUCCESS;
        break;

    default:
        return FAILURE;
    }
    if (opts->curOptIdx >= opts->origArgCt)
        return FAILURE;

    opt_txt[ (*opt_idx)++ ] = opts->origArgVect[ (opts->curOptIdx)++ ];
    return SUCCESS;
}