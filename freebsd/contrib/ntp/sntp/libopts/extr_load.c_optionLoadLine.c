#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fOptSet; } ;
typedef  TYPE_1__ tOptions ;
typedef  int /*<<< orphan*/  tOptState ;
typedef  int /*<<< orphan*/  proc_state_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGDUPSTR (char*,char const*,char*) ; 
 int /*<<< orphan*/  AGFREE (char*) ; 
 int /*<<< orphan*/  DIRECTION_CALLED ; 
 int /*<<< orphan*/  OPTION_LOAD_COOKED ; 
 int /*<<< orphan*/  OPTPROC_ERRSTOP ; 
 int /*<<< orphan*/  OPTSTATE_INITIALIZER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  load_opt_line (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
optionLoadLine(tOptions * opts, char const * line)
{
    tOptState st = OPTSTATE_INITIALIZER(SET);
    char *    pz;
    proc_state_mask_t sv_flags = opts->fOptSet;
    opts->fOptSet &= ~OPTPROC_ERRSTOP;
    AGDUPSTR(pz, line, "opt line");
    load_opt_line(opts, &st, pz, DIRECTION_CALLED, OPTION_LOAD_COOKED);
    AGFREE(pz);
    opts->fOptSet = sv_flags;
}