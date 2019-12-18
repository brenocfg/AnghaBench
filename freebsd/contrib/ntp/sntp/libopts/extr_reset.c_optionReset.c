#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * originalOptArgCookie; TYPE_2__* originalOptArgArray; } ;
typedef  TYPE_3__ tOptions ;
struct TYPE_9__ {int /*<<< orphan*/  argString; } ;
struct TYPE_12__ {size_t optIndex; int /*<<< orphan*/  fOptState; int /*<<< orphan*/  optCookie; TYPE_1__ optArg; int /*<<< orphan*/  (* pOptProc ) (TYPE_3__*,TYPE_4__*) ;} ;
typedef  TYPE_4__ tOptDesc ;
struct TYPE_10__ {int /*<<< orphan*/  argString; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTST_PERSISTENT_MASK ; 
 int /*<<< orphan*/  OPTST_RESET ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void
optionReset(tOptions * pOpts, tOptDesc * pOD)
{
    pOD->fOptState &= OPTST_PERSISTENT_MASK;
    pOD->fOptState |= OPTST_RESET;
    if (pOD->pOptProc != NULL)
        pOD->pOptProc(pOpts, pOD);
    pOD->optArg.argString =
        pOpts->originalOptArgArray[ pOD->optIndex ].argString;
    pOD->optCookie = pOpts->originalOptArgCookie[ pOD->optIndex ];
    pOD->fOptState &= OPTST_PERSISTENT_MASK;
}