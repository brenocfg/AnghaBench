#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* argString; } ;
struct TYPE_10__ {int optCt; int fOptState; char* pSavedState; struct TYPE_10__* pOptDesc; int /*<<< orphan*/ * optCookie; TYPE_1__ optArg; } ;
typedef  TYPE_2__ tOptions ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (char*) ; 
#define  OPARG_TYPE_HIERARCHY 129 
#define  OPARG_TYPE_STRING 128 
 int OPTST_ALLOC_ARG ; 
 int OPTST_GET_ARGTYPE (int) ; 
 int OPTST_STACKED ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  optionUnstackArg (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  unload_arg_list (int /*<<< orphan*/ *) ; 

void
optionFree(tOptions * pOpts)
{
 free_saved_state:
    {
        tOptDesc * p = pOpts->pOptDesc;
        int ct = pOpts->optCt;
        do  {
            if (p->fOptState & OPTST_ALLOC_ARG) {
                AGFREE(p->optArg.argString);
                p->optArg.argString = NULL;
                p->fOptState &= ~OPTST_ALLOC_ARG;
            }

            switch (OPTST_GET_ARGTYPE(p->fOptState)) {
            case OPARG_TYPE_STRING:
#ifdef WITH_LIBREGEX
                if (  (p->fOptState & OPTST_STACKED)
                   && (p->optCookie != NULL)) {
                    p->optArg.argString = ".*";
                    optionUnstackArg(pOpts, p);
                }
#else
                /* leak memory */;
#endif
                break;

            case OPARG_TYPE_HIERARCHY:
                if (p->optCookie != NULL)
                    unload_arg_list(p->optCookie);
                break;
            }

            p->optCookie = NULL;
        } while (p++, --ct > 0);
    }
    if (pOpts->pSavedState != NULL) {
        tOptions * p = (tOptions *)pOpts->pSavedState;
        memcpy(pOpts, p, sizeof(*p));
        memcpy(pOpts->pOptDesc, p+1, (size_t)p->optCt * sizeof(tOptDesc));
        AGFREE(pOpts->pSavedState);
        pOpts->pSavedState = NULL;
        goto free_saved_state;
    }
}