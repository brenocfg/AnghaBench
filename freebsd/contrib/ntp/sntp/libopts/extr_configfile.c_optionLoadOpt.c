#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int fOptSet; int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_9__ {int /*<<< orphan*/  argString; } ;
struct TYPE_11__ {int fOptState; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_CALLED ; 
 scalar_t__ DISABLED_OPT (TYPE_3__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 TYPE_2__* OPTPROC_EMIT_LIMIT ; 
 int OPTPROC_ERRSTOP ; 
 int OPTST_RESET ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  file_preset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fserr_exit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

void
optionLoadOpt(tOptions * opts, tOptDesc * odesc)
{
    struct stat sb;

    if (opts <= OPTPROC_EMIT_LIMIT)
        return;

    /*
     *  IF the option is not being disabled, THEN load the file.  There must
     *  be a file.  (If it is being disabled, then the disablement processing
     *  already took place.  It must be done to suppress preloading of ini/rc
     *  files.)
     */
    if (  DISABLED_OPT(odesc)
       || ((odesc->fOptState & OPTST_RESET) != 0))
        return;

    if (stat(odesc->optArg.argString, &sb) != 0) {
        if ((opts->fOptSet & OPTPROC_ERRSTOP) == 0)
            return;

        fserr_exit(opts->pzProgName, "stat", odesc->optArg.argString);
        /* NOT REACHED */
    }

    if (! S_ISREG(sb.st_mode)) {
        if ((opts->fOptSet & OPTPROC_ERRSTOP) == 0)
            return;
        errno = EINVAL;
        fserr_exit(opts->pzProgName, "stat", odesc->optArg.argString);
        /* NOT REACHED */
    }

    file_preset(opts, odesc->optArg.argString, DIRECTION_CALLED);
}