#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_7__ {scalar_t__ curOptIdx; scalar_t__ origArgCt; int /*<<< orphan*/ * pzCurOpt; int /*<<< orphan*/  pzProgPath; int /*<<< orphan*/ ** origArgVect; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_8__ {int optType; TYPE_1__* pOD; int /*<<< orphan*/ * pzOptArg; } ;
typedef  TYPE_3__ tOptState ;
struct TYPE_6__ {int /*<<< orphan*/  pz_Name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  NUL ; 
 int /*<<< orphan*/  SUCCESS ; 
#define  TOPT_DEFAULT 130 
#define  TOPT_LONG 129 
#define  TOPT_SHORT 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* zMisArg ; 

__attribute__((used)) static tSuccess
get_opt_arg_must(tOptions * opts, tOptState * o_st)
{
    switch (o_st->optType) {
    case TOPT_SHORT:
        /*
         *  See if an arg string follows the flag character
         */
        if (*++(opts->pzCurOpt) == NUL)
            opts->pzCurOpt = opts->origArgVect[ opts->curOptIdx++ ];
        o_st->pzOptArg = opts->pzCurOpt;
        break;

    case TOPT_LONG:
        /*
         *  See if an arg string has already been assigned (glued on
         *  with an `=' character)
         */
        if (o_st->pzOptArg == NULL)
            o_st->pzOptArg = opts->origArgVect[ opts->curOptIdx++ ];
        break;

    default:
#ifdef DEBUG
        fputs("AutoOpts lib error: option type not selected\n", stderr);
        option_exits(EXIT_FAILURE);
#endif

    case TOPT_DEFAULT:
        /*
         *  The option was selected by default.  The current token is
         *  the option argument.
         */
        break;
    }

    /*
     *  Make sure we did not overflow the argument list.
     */
    if (opts->curOptIdx > opts->origArgCt) {
        fprintf(stderr, zMisArg, opts->pzProgPath, o_st->pOD->pz_Name);
        return FAILURE;
    }

    opts->pzCurOpt = NULL;  /* next time advance to next arg */
    return SUCCESS;
}