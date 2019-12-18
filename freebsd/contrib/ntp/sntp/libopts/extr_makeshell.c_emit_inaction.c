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
struct TYPE_5__ {int /*<<< orphan*/  pzPROGNAME; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {scalar_t__ pOptProc; int optMaxCt; int /*<<< orphan*/  pz_DisablePfx; int /*<<< orphan*/  pz_NAME; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 char* LVL3_CMD ; 
 int /*<<< orphan*/  NO_ARG_NEEDED ; 
 char* NO_MULTI_ARG_FMT ; 
 char* NO_SGL_ARG_FMT ; 
 int /*<<< orphan*/  NO_SUPPRESS_LOAD ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optionLoadOpt ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  zOptionEndSelect ; 

__attribute__((used)) static void
emit_inaction(tOptions * opts, tOptDesc * od)
{
    if (od->pOptProc == optionLoadOpt) {
        printf(LVL3_CMD, NO_SUPPRESS_LOAD);

    } else if (od->optMaxCt == 1)
        printf(NO_SGL_ARG_FMT, opts->pzPROGNAME,
               od->pz_NAME, od->pz_DisablePfx);
    else
        printf(NO_MULTI_ARG_FMT, opts->pzPROGNAME,
               od->pz_NAME, od->pz_DisablePfx);

    printf(LVL3_CMD, NO_ARG_NEEDED);
    fputs(zOptionEndSelect, stdout);
}