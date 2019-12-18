#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  paramValues_t ;
typedef  int /*<<< orphan*/  contexts_t ;
typedef  int /*<<< orphan*/  buffers_t ;
typedef  int /*<<< orphan*/  BMK_benchResult_t ;
typedef  int /*<<< orphan*/  BMK_benchOutcome_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_CLEVEL ; 
 int /*<<< orphan*/  BMK_benchMemInvertible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BMK_both ; 
 int /*<<< orphan*/  BMK_extract_benchResult (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BMK_isSuccessful_benchOutcome (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int BMK_benchParam ( BMK_benchResult_t* resultPtr,
                            buffers_t buf, contexts_t ctx,
                            paramValues_t cParams)
{
    BMK_benchOutcome_t const outcome = BMK_benchMemInvertible(buf, ctx,
                                                        BASE_CLEVEL, &cParams,
                                                        BMK_both, 3);
    if (!BMK_isSuccessful_benchOutcome(outcome)) return 1;
    *resultPtr = BMK_extract_benchResult(outcome);
    return 0;
}