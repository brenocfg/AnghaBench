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
typedef  scalar_t__ time_t ;
struct TYPE_10__ {int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_9__ {long argInt; int /*<<< orphan*/  argString; } ;
struct TYPE_11__ {int fOptState; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (int /*<<< orphan*/ ) ; 
 scalar_t__ BAD_TIME ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ INQUERY_CALL (TYPE_2__*,TYPE_3__*) ; 
 int OPTPROC_ERRSTOP ; 
 int OPTST_ALLOC_ARG ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_duration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* zNotDuration ; 

void
optionTimeVal(tOptions * opts, tOptDesc * od)
{
    time_t val;

    if (INQUERY_CALL(opts, od))
        return;

    val = parse_duration(od->optArg.argString);
    if (val == BAD_TIME) {
        fprintf(stderr, zNotDuration, opts->pzProgName, od->optArg.argString);
        if ((opts->fOptSet & OPTPROC_ERRSTOP) != 0)
            (*(opts->pUsageProc))(opts, EXIT_FAILURE);
    }

    if (od->fOptState & OPTST_ALLOC_ARG) {
        AGFREE(od->optArg.argString);
        od->fOptState &= ~OPTST_ALLOC_ARG;
    }

    od->optArg.argInt = (long)val;
}