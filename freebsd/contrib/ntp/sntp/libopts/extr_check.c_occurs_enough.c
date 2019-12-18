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
struct TYPE_5__ {int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {int optOccCt; int optMinCt; int fOptState; int /*<<< orphan*/  pz_Name; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int OPTST_MUST_SET ; 
 int OPTST_PRESET ; 
 int OPTST_SET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* zneed_more ; 
 char* zneed_one ; 

__attribute__((used)) static bool
occurs_enough(tOptions * pOpts, tOptDesc * pOD)
{
    (void)pOpts;

    /*
     *  IF the occurrence counts have been satisfied,
     *  THEN there is no problem.
     */
    if (pOD->optOccCt >= pOD->optMinCt)
        return true;

    /*
     *  IF MUST_SET means SET and PRESET are okay,
     *  so min occurrence count doesn't count
     */
    if (  (pOD->fOptState & OPTST_MUST_SET)
       && (pOD->fOptState & (OPTST_PRESET | OPTST_SET)) )
        return true;

    if (pOD->optMinCt > 1)
         fprintf(stderr, zneed_more, pOpts->pzProgName, pOD->pz_Name,
                 pOD->optMinCt);
    else fprintf(stderr, zneed_one,  pOpts->pzProgName, pOD->pz_Name);
    return false;
}