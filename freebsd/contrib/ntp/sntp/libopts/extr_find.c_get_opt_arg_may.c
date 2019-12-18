#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_6__ {char* pzCurOpt; char** origArgVect; size_t curOptIdx; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_7__ {int optType; char* pzOptArg; } ;
typedef  TYPE_2__ tOptState ;

/* Variables and functions */
 int /*<<< orphan*/  NAMED_OPTS (TYPE_1__*) ; 
 char NUL ; 
 int /*<<< orphan*/  SUCCESS ; 
#define  TOPT_DEFAULT 130 
#define  TOPT_LONG 129 
#define  TOPT_SHORT 128 
 int /*<<< orphan*/  ao_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbad_default_msg ; 

__attribute__((used)) static tSuccess
get_opt_arg_may(tOptions * pOpts, tOptState * o_st)
{
    /*
     *  An option argument is optional.
     */
    switch (o_st->optType) {
    case TOPT_SHORT:
        if (*++pOpts->pzCurOpt != NUL)
            o_st->pzOptArg = pOpts->pzCurOpt;
        else {
            char * pzLA = pOpts->origArgVect[ pOpts->curOptIdx ];

            /*
             *  BECAUSE it is optional, we must make sure
             *  we did not find another flag and that there
             *  is such an argument.
             */
            if ((pzLA == NULL) || (*pzLA == '-'))
                o_st->pzOptArg = NULL;
            else {
                pOpts->curOptIdx++; /* argument found */
                o_st->pzOptArg = pzLA;
            }
        }
        break;

    case TOPT_LONG:
        /*
         *  Look for an argument if we don't already have one (glued on
         *  with a `=' character) *AND* we are not in named argument mode
         */
        if (  (o_st->pzOptArg == NULL)
           && (! NAMED_OPTS(pOpts))) {
            char * pzLA = pOpts->origArgVect[ pOpts->curOptIdx ];

            /*
             *  BECAUSE it is optional, we must make sure
             *  we did not find another flag and that there
             *  is such an argument.
             */
            if ((pzLA == NULL) || (*pzLA == '-'))
                o_st->pzOptArg = NULL;
            else {
                pOpts->curOptIdx++; /* argument found */
                o_st->pzOptArg = pzLA;
            }
        }
        break;

    default:
    case TOPT_DEFAULT:
        ao_bug(zbad_default_msg);
    }

    /*
     *  After an option with an optional argument, we will
     *  *always* start with the next option because if there
     *  were any characters following the option name/flag,
     *  they would be interpreted as the argument.
     */
    pOpts->pzCurOpt = NULL;
    return SUCCESS;
}