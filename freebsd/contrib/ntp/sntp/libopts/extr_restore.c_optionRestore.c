#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* pzProgName; char* pzPROGNAME; struct TYPE_7__* pSavedState; scalar_t__ optCt; struct TYPE_7__* pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
typedef  int /*<<< orphan*/  tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  fixupSavedOptionArgs (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  optionFree (TYPE_1__*) ; 
 int /*<<< orphan*/  option_exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* zNil ; 
 char* zNoState ; 

void
optionRestore(tOptions * pOpts)
{
    tOptions * p = (tOptions *)pOpts->pSavedState;

    if (p == NULL) {
        char const * pzName = pOpts->pzProgName;
        if (pzName == NULL) {
            pzName = pOpts->pzPROGNAME;
            if (pzName == NULL)
                pzName = zNil;
        }
        fprintf(stderr, zNoState, pzName);
        option_exits(EXIT_FAILURE);
    }

    pOpts->pSavedState = NULL;
    optionFree(pOpts);

    memcpy(pOpts, p, sizeof(*p));
    memcpy(pOpts->pOptDesc, p+1, (size_t)p->optCt * sizeof(tOptDesc));
    pOpts->pSavedState = p;

    fixupSavedOptionArgs(pOpts);
}