#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int optCt; int /*<<< orphan*/  pzPROGNAME; TYPE_2__* pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_12__ {int /*<<< orphan*/ * pz_DisableName; int /*<<< orphan*/ * pz_Name; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  OPTION_STR ; 
 scalar_t__ SKIP_OPT (TYPE_2__*) ; 
 char* UNK_OPT_FMT ; 
 int /*<<< orphan*/  emit_action (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  emit_inaction (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  emit_match_expr (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  zOptionCase ; 

__attribute__((used)) static void
emit_long(tOptions * opts)
{
    tOptDesc * od = opts->pOptDesc;
    int        ct  = opts->optCt;

    fputs(zOptionCase, stdout);

    /*
     *  do each option, ...
     */
    do  {
        /*
         *  Documentation & compiled-out options
         */
        if (SKIP_OPT(od))
            continue;

        emit_match_expr(od->pz_Name, od, opts);
        emit_action(opts, od);

        /*
         *  Now, do the same thing for the disablement version of the option.
         */
        if (od->pz_DisableName != NULL) {
            emit_match_expr(od->pz_DisableName, od, opts);
            emit_inaction(opts, od);
        }
    } while (od++, --ct > 0);

    printf(UNK_OPT_FMT, OPTION_STR, opts->pzPROGNAME);
}