#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dictSize; } ;
typedef  TYPE_1__ contexts_t ;
struct TYPE_8__ {int /*<<< orphan*/  srcSize; int /*<<< orphan*/  maxBlockSize; } ;
typedef  TYPE_2__ buffers_t ;
typedef  int /*<<< orphan*/  BMK_benchResult_t ;

/* Variables and functions */
 scalar_t__ BMK_benchParam (int /*<<< orphan*/ *,TYPE_2__ const,TYPE_1__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMK_printWinner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUSTOM_LEVEL ; 
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int /*<<< orphan*/  ZSTD_getCParams (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjustParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cParamsToPVals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_params ; 
 int /*<<< orphan*/  overwriteParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
benchOnce(const buffers_t buf, const contexts_t ctx, const int cLevel)
{
    BMK_benchResult_t testResult;
    g_params = adjustParams(overwriteParams(cParamsToPVals(ZSTD_getCParams(cLevel, buf.maxBlockSize, ctx.dictSize)), g_params), buf.maxBlockSize, ctx.dictSize);

    if (BMK_benchParam(&testResult, buf, ctx, g_params)) {
        DISPLAY("Error during benchmarking\n");
        return 1;
    }

    BMK_printWinner(stdout, CUSTOM_LEVEL, testResult, g_params, buf.srcSize);

    return 0;
}