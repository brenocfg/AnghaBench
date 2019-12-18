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
typedef  int /*<<< orphan*/  UTIL_time_t ;
struct TYPE_6__ {size_t blockCount; size_t (* benchFn ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;size_t* blockResults; scalar_t__* srcSizes; scalar_t__ (* errorFn ) (size_t const) ;int /*<<< orphan*/  benchPayload; int /*<<< orphan*/ * dstCapacities; int /*<<< orphan*/ * dstBuffers; int /*<<< orphan*/ * srcBuffers; int /*<<< orphan*/  initPayload; int /*<<< orphan*/  (* initFn ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {double nanoSecPerRun; size_t sumOfReturn; } ;
typedef  scalar_t__ PTime ;
typedef  TYPE_1__ BMK_runTime_t ;
typedef  int /*<<< orphan*/  BMK_runOutcome_t ;
typedef  TYPE_2__ BMK_benchParams_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_runOutcome_error (size_t const) ; 
 int /*<<< orphan*/  BMK_setValid_runTime (TYPE_1__) ; 
 int /*<<< orphan*/  RETURN_QUIET_ERROR (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int) ; 
 scalar_t__ UTIL_clockSpanNano (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  UTIL_getTime () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 size_t stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (size_t const) ; 

BMK_runOutcome_t BMK_benchFunction(BMK_benchParams_t p,
                                   unsigned nbLoops)
{
    size_t dstSize = 0;
    nbLoops += !nbLoops;   /* minimum nbLoops is 1 */

    /* init */
    {   size_t i;
        for(i = 0; i < p.blockCount; i++) {
            memset(p.dstBuffers[i], 0xE5, p.dstCapacities[i]);  /* warm up and erase result buffer */
    }   }

    /* benchmark */
    {   UTIL_time_t const clockStart = UTIL_getTime();
        unsigned loopNb, blockNb;
        if (p.initFn != NULL) p.initFn(p.initPayload);
        for (loopNb = 0; loopNb < nbLoops; loopNb++) {
            for (blockNb = 0; blockNb < p.blockCount; blockNb++) {
                size_t const res = p.benchFn(p.srcBuffers[blockNb], p.srcSizes[blockNb],
                                   p.dstBuffers[blockNb], p.dstCapacities[blockNb],
                                   p.benchPayload);
                if (loopNb == 0) {
                    if (p.blockResults != NULL) p.blockResults[blockNb] = res;
                    if ((p.errorFn != NULL) && (p.errorFn(res))) {
                        RETURN_QUIET_ERROR(BMK_runOutcome_error(res),
                            "Function benchmark failed on block %u (of size %u) with error %i",
                            blockNb, (unsigned)p.srcSizes[blockNb], (int)res);
                    }
                    dstSize += res;
            }   }
        }  /* for (loopNb = 0; loopNb < nbLoops; loopNb++) */

        {   PTime const totalTime = UTIL_clockSpanNano(clockStart);
            BMK_runTime_t rt;
            rt.nanoSecPerRun = (double)totalTime / nbLoops;
            rt.sumOfReturn = dstSize;
            return BMK_setValid_runTime(rt);
    }   }
}