#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  file_mode; } ;
typedef  TYPE_2__ tuFileMode ;
struct TYPE_10__ {int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_3__ tOptions ;
struct TYPE_8__ {int /*<<< orphan*/ * argFp; int /*<<< orphan*/  argString; } ;
struct TYPE_11__ {int fOptState; TYPE_1__ optArg; int /*<<< orphan*/  optCookie; } ;
typedef  TYPE_4__ tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AGDUPSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int OPTST_ALLOC_ARG ; 
 int /*<<< orphan*/  VOIDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fserr_exit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fopen_file_fp(tOptions * pOpts, tOptDesc * pOD, tuFileMode mode)
{
    FILE * fp = fopen(pOD->optArg.argString, mode.file_mode);
    if (fp == NULL)
        fserr_exit(pOpts->pzProgName, "fopen", pOD->optArg.argString);
        /* NOTREACHED */

    if ((pOD->fOptState & OPTST_ALLOC_ARG) != 0)
        pOD->optCookie = VOIDP(pOD->optArg.argString);
    else
        AGDUPSTR(pOD->optCookie, pOD->optArg.argString, "file name");

    pOD->optArg.argFp = fp;
    pOD->fOptState &= ~OPTST_ALLOC_ARG;
}