#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double nanoSecPerRun; size_t sumOfReturn; } ;
struct TYPE_5__ {int timeBudget_ns; int runBudget_ns; int nbLoops; int /*<<< orphan*/  coolTime; TYPE_1__ fastestRun; scalar_t__ timeSpent_ns; } ;
typedef  int PTime ;
typedef  TYPE_2__ BMK_timedFnState_t ;

/* Variables and functions */
 int TIMELOOP_NANOSEC ; 
 int /*<<< orphan*/  UTIL_getTime () ; 

void BMK_resetTimedFnState(BMK_timedFnState_t* timedFnState, unsigned total_ms, unsigned run_ms)
{
    if (!total_ms) total_ms = 1 ;
    if (!run_ms) run_ms = 1;
    if (run_ms > total_ms) run_ms = total_ms;
    timedFnState->timeSpent_ns = 0;
    timedFnState->timeBudget_ns = (PTime)total_ms * TIMELOOP_NANOSEC / 1000;
    timedFnState->runBudget_ns = (PTime)run_ms * TIMELOOP_NANOSEC / 1000;
    timedFnState->fastestRun.nanoSecPerRun = (double)TIMELOOP_NANOSEC * 2000000000;  /* hopefully large enough : must be larger than any potential measurement */
    timedFnState->fastestRun.sumOfReturn = (size_t)(-1LL);
    timedFnState->nbLoops = 1;
    timedFnState->coolTime = UTIL_getTime();
}