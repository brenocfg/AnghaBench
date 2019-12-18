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
struct TYPE_5__ {int optCt; TYPE_2__* pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {scalar_t__* pz_Name; int fOptState; scalar_t__* pz_DisableName; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int OPTST_NO_INIT ; 
 int OPTST_OMITTED ; 
 scalar_t__ SKIP_OPT (TYPE_2__*) ; 
 scalar_t__ strneqvcmp (char const*,scalar_t__*,int) ; 

__attribute__((used)) static int
opt_match_ct(tOptions * opts, char const * name, int nm_len,
             int * ixp, bool * disable)
{
    int   matchCt  = 0;
    int   idx      = 0;
    int   idxLim   = opts->optCt;
    tOptDesc * pOD = opts->pOptDesc;

    do  {
        /*
         *  If option disabled or a doc option, skip to next
         */
        if (pOD->pz_Name == NULL)
            continue;

        if (  SKIP_OPT(pOD)
           && (pOD->fOptState != (OPTST_OMITTED | OPTST_NO_INIT)))
            continue;

        if (strneqvcmp(name, pOD->pz_Name, nm_len) == 0) {
            /*
             *  IF we have a complete match
             *  THEN it takes priority over any already located partial
             */
            if (pOD->pz_Name[ nm_len ] == NUL) {
                *ixp = idx;
                return 1;
            }
        }

        /*
         *  IF       there is a disable name
         *     *AND* the option name matches the disable name
         *  THEN ...
         */
        else if (  (pOD->pz_DisableName != NULL)
                && (strneqvcmp(name, pOD->pz_DisableName, nm_len) == 0)
                )  {
            *disable = true;

            /*
             *  IF we have a complete match
             *  THEN it takes priority over any already located partial
             */
            if (pOD->pz_DisableName[ nm_len ] == NUL) {
                *ixp = idx;
                return 1;
            }
        }

        else
            continue; /* does not match any option */

        /*
         *  We found a full or partial match, either regular or disabling.
         *  Remember the index for later.
         */
        *ixp = idx;
        ++matchCt;

    } while (pOD++, (++idx < idxLim));

    return matchCt;
}