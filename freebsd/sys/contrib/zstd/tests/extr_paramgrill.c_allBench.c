#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  paramValues_t ;
typedef  int /*<<< orphan*/  contexts_t ;
typedef  int /*<<< orphan*/  constraint_t ;
struct TYPE_12__ {scalar_t__ srcSize; } ;
typedef  TYPE_1__ buffers_t ;
typedef  double U64 ;
struct TYPE_13__ {scalar_t__ cSize; int cSpeed; int dSpeed; } ;
typedef  TYPE_2__ BMK_benchResult_t ;
typedef  int /*<<< orphan*/  BMK_benchOutcome_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_CLEVEL ; 
 int BETTER_RESULT ; 
 int /*<<< orphan*/  BMK_benchMemInvertible (TYPE_1__ const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BMK_both ; 
 TYPE_2__ BMK_extract_benchResult (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BMK_isSuccessful_benchOutcome (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DEBUGOUTPUT (char*,...) ; 
 int ERROR_RESULT ; 
 double TIMELOOP_NANOSEC ; 
 double VARIANCE ; 
 int WORSE_RESULT ; 
 scalar_t__ compareResultLT (TYPE_2__,TYPE_2__,int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  feasible (TYPE_2__,int /*<<< orphan*/  const) ; 
 int g_clockGranularity ; 
 int /*<<< orphan*/  g_optmode ; 
 double resultScore (TYPE_2__,scalar_t__,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int allBench(BMK_benchResult_t* resultPtr,
                const buffers_t buf, const contexts_t ctx,
                const paramValues_t cParams,
                const constraint_t target,
                BMK_benchResult_t* winnerResult, int feas)
{
    BMK_benchResult_t benchres;
    double uncertaintyConstantC = 3., uncertaintyConstantD = 3.;
    double winnerRS;

    BMK_benchOutcome_t const outcome = BMK_benchMemInvertible(buf, ctx, BASE_CLEVEL, &cParams, BMK_both, 2);
    if (!BMK_isSuccessful_benchOutcome(outcome)) {
        DEBUGOUTPUT("Benchmarking failed \n");
        return ERROR_RESULT;
    }
    benchres = BMK_extract_benchResult(outcome);

    winnerRS = resultScore(*winnerResult, buf.srcSize, target);
    DEBUGOUTPUT("WinnerScore: %f \n ", winnerRS);

    *resultPtr = benchres;

    /* anything with worse ratio in feas is definitely worse, discard */
    if(feas && benchres.cSize < winnerResult->cSize && !g_optmode) {
        return WORSE_RESULT;
    }

    /* calculate uncertainty in compression / decompression runs */
    if (benchres.cSpeed) {
        U64 const loopDurationC = (((U64)buf.srcSize * TIMELOOP_NANOSEC) / benchres.cSpeed);
        uncertaintyConstantC = ((loopDurationC + (double)(2 * g_clockGranularity))/loopDurationC);
    }

    if (benchres.dSpeed) {
        U64 const loopDurationD = (((U64)buf.srcSize * TIMELOOP_NANOSEC) / benchres.dSpeed);
        uncertaintyConstantD = ((loopDurationD + (double)(2 * g_clockGranularity))/loopDurationD);
    }

    /* optimistic assumption of benchres */
    {   BMK_benchResult_t resultMax = benchres;
        resultMax.cSpeed = (unsigned long long)(resultMax.cSpeed * uncertaintyConstantC * VARIANCE);
        resultMax.dSpeed = (unsigned long long)(resultMax.dSpeed * uncertaintyConstantD * VARIANCE);

        /* disregard infeasible results in feas mode */
        /* disregard if resultMax < winner in infeas mode */
        if((feas && !feasible(resultMax, target)) ||
          (!feas && (winnerRS > resultScore(resultMax, buf.srcSize, target)))) {
            return WORSE_RESULT;
        }
    }

    /* compare by resultScore when in infeas */
    /* compare by compareResultLT when in feas */
    if((!feas && (resultScore(benchres, buf.srcSize, target) > resultScore(*winnerResult, buf.srcSize, target))) ||
       (feas && (compareResultLT(*winnerResult, benchres, target, buf.srcSize))) )  {
        return BETTER_RESULT;
    } else {
        return WORSE_RESULT;
    }
}