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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_9__ {char** origArgVect; size_t curOptIdx; size_t origArgCt; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_10__ {TYPE_1__* pOD; } ;
typedef  TYPE_3__ tOptState ;
struct TYPE_8__ {int fOptState; } ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAILURE ; 
 char NUL ; 
 scalar_t__ OPARG_TYPE_NONE ; 
 int OPTST_ARG_OPTIONAL ; 
 scalar_t__ OPTST_GET_ARGTYPE (int) ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  opt_find_short (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static tSuccess
short_opt_ck(tOptions * opts, char * arg_txt, tOptState * pOS,
             char ** opt_txt, uint32_t * opt_idx)
{
    while (*arg_txt != NUL) {
        if (FAILED(opt_find_short(opts, (uint8_t)*arg_txt, pOS)))
            return FAILURE;

        /*
         *  See if we can have an arg.
         */
        if (OPTST_GET_ARGTYPE(pOS->pOD->fOptState) == OPARG_TYPE_NONE) {
            arg_txt++;

        } else if (pOS->pOD->fOptState & OPTST_ARG_OPTIONAL) {
            /*
             *  Take an argument if it is not attached and it does not
             *  start with a hyphen.
             */
            if (arg_txt[1] != NUL)
                return SUCCESS;

            arg_txt = opts->origArgVect[ opts->curOptIdx ];
            if (*arg_txt != '-')
                opt_txt[ (*opt_idx)++ ] =
                    opts->origArgVect[ (opts->curOptIdx)++ ];
            return SUCCESS;

        } else {
            /*
             *  IF we need another argument, be sure it is there and
             *  take it.
             */
            if (arg_txt[1] == NUL) {
                if (opts->curOptIdx >= opts->origArgCt)
                    return FAILURE;
                opt_txt[ (*opt_idx)++ ] =
                    opts->origArgVect[ (opts->curOptIdx)++ ];
            }
            return SUCCESS;
        }
    }
    return SUCCESS;
}