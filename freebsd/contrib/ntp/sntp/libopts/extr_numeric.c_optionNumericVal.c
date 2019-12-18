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
struct TYPE_10__ {int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_9__ {char* argString; long argInt; } ;
struct TYPE_11__ {int fOptState; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (char*) ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ INQUERY_CALL (TYPE_2__*,TYPE_3__*) ; 
#define  NUL 128 
 int OPTPROC_ERRSTOP ; 
 int OPTST_ALLOC_ARG ; 
 int OPTST_RESET ; 
 int OPTST_SCALED_NUM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* zNotNumber ; 

void
optionNumericVal(tOptions * opts, tOptDesc * od)
{
    char * pz;
    long   val;

    /*
     *  Guard against all the different ways this procedure might get invoked
     *  when there is no string argument provided.
     */
    if (INQUERY_CALL(opts, od) || (od->optArg.argString == NULL))
        return;

    /*
     *  Numeric options may have a range associated with it.
     *  If it does, the usage procedure requests that it be
     *  emitted by passing a NULL od pointer.  Also bail out
     *  if there is no option argument or if we are being reset.
     */
    if (  (od == NULL)
       || (od->optArg.argString == NULL)
       || ((od->fOptState & OPTST_RESET) != 0))
        return;

    errno = 0;
    val = strtol(od->optArg.argString, &pz, 0);
    if ((pz == od->optArg.argString) || (errno != 0))
        goto bad_number;

    if ((od->fOptState & OPTST_SCALED_NUM) != 0)
        switch (*(pz++)) {
        case NUL:  pz--; break;
        case 't':  val *= 1000;
        case 'g':  val *= 1000;
        case 'm':  val *= 1000;
        case 'k':  val *= 1000; break;

        case 'T':  val *= 1024;
        case 'G':  val *= 1024;
        case 'M':  val *= 1024;
        case 'K':  val *= 1024; break;

        default:   goto bad_number;
        }

    if (*pz != NUL)
        goto bad_number;

    if (od->fOptState & OPTST_ALLOC_ARG) {
        AGFREE(od->optArg.argString);
        od->fOptState &= ~OPTST_ALLOC_ARG;
    }

    od->optArg.argInt = val;
    return;

    bad_number:

    fprintf( stderr, zNotNumber, opts->pzProgName, od->optArg.argString );
    if ((opts->fOptSet & OPTPROC_ERRSTOP) != 0)
        (*(opts->pUsageProc))(opts, EXIT_FAILURE);

    errno = EINVAL;
    od->optArg.argInt = ~0;
}