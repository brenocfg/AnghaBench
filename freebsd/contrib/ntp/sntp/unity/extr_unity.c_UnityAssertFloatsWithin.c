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
typedef  float _UF ;
typedef  int /*<<< orphan*/  UNITY_LINE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_FAIL_AND_BAIL ; 
 int /*<<< orphan*/  UNITY_SKIP_EXECUTION ; 
 int /*<<< orphan*/  UnityAddMsgIfSpecified (char const*) ; 
 int /*<<< orphan*/  UnityPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnityPrintFloat (float const) ; 
 int /*<<< orphan*/  UnityStrDelta ; 
 int /*<<< orphan*/  UnityStrExpected ; 
 int /*<<< orphan*/  UnityStrWas ; 
 int /*<<< orphan*/  UnityTestResultsFailBegin (int /*<<< orphan*/  const) ; 

void UnityAssertFloatsWithin(const _UF delta,
                             const _UF expected,
                             const _UF actual,
                             const char* msg,
                             const UNITY_LINE_TYPE lineNumber)
{
    _UF diff = actual - expected;
    _UF pos_delta = delta;

    UNITY_SKIP_EXECUTION;

    if (diff < 0.0f)
    {
        diff = 0.0f - diff;
    }
    if (pos_delta < 0.0f)
    {
        pos_delta = 0.0f - pos_delta;
    }

    //This first part of this condition will catch any NaN or Infinite values
    if ((diff * 0.0f != 0.0f) || (pos_delta < diff))
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_FLOAT_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrintFloat(expected);
        UnityPrint(UnityStrWas);
        UnityPrintFloat(actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
}