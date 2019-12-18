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
struct TYPE_7__ {int /*<<< orphan*/ * pzCurOpt; int /*<<< orphan*/  pzProgPath; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_8__ {scalar_t__ optType; TYPE_1__* pOD; int /*<<< orphan*/ * pzOptArg; } ;
typedef  TYPE_3__ tOptState ;
struct TYPE_6__ {int /*<<< orphan*/  pz_Name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  SUCCESS ; 
 scalar_t__ TOPT_SHORT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* zNoArg ; 

__attribute__((used)) static tSuccess
get_opt_arg_none(tOptions * pOpts, tOptState * o_st)
{
    /*
     *  No option argument.  Make sure next time around we find
     *  the correct option flag character for short options
     */
    if (o_st->optType == TOPT_SHORT)
        (pOpts->pzCurOpt)++;

    /*
     *  It is a long option.  Make sure there was no ``=xxx'' argument
     */
    else if (o_st->pzOptArg != NULL) {
        fprintf(stderr, zNoArg, pOpts->pzProgPath, o_st->pOD->pz_Name);
        return FAILURE;
    }

    /*
     *  It is a long option.  Advance to next command line argument.
     */
    else
        pOpts->pzCurOpt = NULL;
    return SUCCESS;
}