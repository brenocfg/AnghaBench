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
typedef  scalar_t__ _U_SINT ;
typedef  int /*<<< orphan*/  UNITY_LINE_TYPE ;
typedef  int /*<<< orphan*/  UNITY_DISPLAY_STYLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_FAIL_AND_BAIL ; 
 int /*<<< orphan*/  UNITY_SKIP_EXECUTION ; 
 int /*<<< orphan*/  UnityAddMsgIfSpecified (char const*) ; 
 int /*<<< orphan*/  UnityPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnityPrintNumberByStyle (scalar_t__ const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  UnityStrExpected ; 
 int /*<<< orphan*/  UnityStrWas ; 
 int /*<<< orphan*/  UnityTestResultsFailBegin (int /*<<< orphan*/  const) ; 

void UnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber,
                            const UNITY_DISPLAY_STYLE_T style)
{
    UNITY_SKIP_EXECUTION;

    if (expected != actual)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrExpected);
        UnityPrintNumberByStyle(expected, style);
        UnityPrint(UnityStrWas);
        UnityPrintNumberByStyle(actual, style);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
}