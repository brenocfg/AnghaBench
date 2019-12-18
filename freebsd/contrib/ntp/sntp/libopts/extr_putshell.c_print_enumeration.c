#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pzPROGNAME; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_7__ {uintptr_t argEnum; int /*<<< orphan*/  argString; } ;
struct TYPE_9__ {int fOptState; int /*<<< orphan*/  pz_NAME; TYPE_1__ optArg; int /*<<< orphan*/  (* pOptProc ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_3__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPTPROC_RETURN_VALNAME ; 
 int OPTST_ALLOC_ARG ; 
 char* OPT_END_FMT ; 
 char* OPT_VAL_FMT ; 
 char* QUOT_ARG_FMT ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
print_enumeration(tOptions * pOpts, tOptDesc * pOD)
{
    uintptr_t e_val = pOD->optArg.argEnum;
    printf(OPT_VAL_FMT, pOpts->pzPROGNAME, pOD->pz_NAME);

    /*
     *  Convert value to string, print that and restore numeric value.
     */
    (*(pOD->pOptProc))(OPTPROC_RETURN_VALNAME, pOD);
    printf(QUOT_ARG_FMT, pOD->optArg.argString);
    if (pOD->fOptState & OPTST_ALLOC_ARG)
        AGFREE(pOD->optArg.argString);
    pOD->optArg.argEnum = e_val;

    printf(OPT_END_FMT, pOpts->pzPROGNAME, pOD->pz_NAME);
}