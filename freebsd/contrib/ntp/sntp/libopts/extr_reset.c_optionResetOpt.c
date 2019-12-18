#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_20__ {int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgPath; int /*<<< orphan*/  pzProgName; int /*<<< orphan*/ * originalOptArgCookie; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_21__ {int /*<<< orphan*/  pOD; } ;
typedef  TYPE_3__ tOptState ;
struct TYPE_19__ {char* argString; } ;
struct TYPE_22__ {char const* pz_Name; TYPE_1__ optArg; } ;
typedef  TYPE_4__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINED ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  HAS_originalOptArgArray (TYPE_2__*) ; 
 char const NUL ; 
 TYPE_2__* OPTPROC_EMIT_LIMIT ; 
 TYPE_3__ OPTSTATE_INITIALIZER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCESSFUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  opt_find_long (TYPE_2__*,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  opt_find_short (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  optionReset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optionResetEverything (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* zIllOptChr ; 
 char* zIllOptStr ; 
 int /*<<< orphan*/  zno_reset ; 
 char* zreset_arg ; 

void
optionResetOpt(tOptions * pOpts, tOptDesc * pOD)
{
    static bool reset_active = false;

    tOptState opt_state = OPTSTATE_INITIALIZER(DEFINED);
    char const * pzArg = pOD->optArg.argString;
    tSuccess     succ;

    if (pOpts <= OPTPROC_EMIT_LIMIT)
        return;

    if (reset_active)
        return;

    if (  (! HAS_originalOptArgArray(pOpts))
       || (pOpts->originalOptArgCookie == NULL))
        ao_bug(zno_reset);

    if ((pzArg == NULL) || (*pzArg == NUL)) {
        fprintf(stderr, zreset_arg, pOpts->pzProgName, pOD->pz_Name);
        pOpts->pUsageProc(pOpts, EXIT_FAILURE);
        /* NOTREACHED */
        assert(0 == 1);
    }

    reset_active = true;

    if (pzArg[1] == NUL) {
        if (*pzArg == '*') {
            optionResetEverything(pOpts);
            reset_active = false;
            return;
        }

        succ = opt_find_short(pOpts, (uint8_t)*pzArg, &opt_state);
        if (! SUCCESSFUL(succ)) {
            fprintf(stderr, zIllOptChr, pOpts->pzProgPath, *pzArg);
            pOpts->pUsageProc(pOpts, EXIT_FAILURE);
            /* NOTREACHED */
            assert(0 == 1);
        }
    } else {
        succ = opt_find_long(pOpts, pzArg, &opt_state);
        if (! SUCCESSFUL(succ)) {
            fprintf(stderr, zIllOptStr, pOpts->pzProgPath, pzArg);
            pOpts->pUsageProc(pOpts, EXIT_FAILURE);
            /* NOTREACHED */
            assert(0 == 1);
        }
    }

    /*
     *  We've found the indicated option.  Turn off all non-persistent
     *  flags because we're forcing the option back to its initialized state.
     *  Call any callout procedure to handle whatever it needs to.
     *  Finally, clear the reset flag, too.
     */
    optionReset(pOpts, opt_state.pOD);
    reset_active = false;
}