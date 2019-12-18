#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* UnityTestFunction ) () ;
typedef  scalar_t__ UNITY_LINE_TYPE ;
struct TYPE_2__ {char const* CurrentTestName; int /*<<< orphan*/  CurrentTestIgnored; int /*<<< orphan*/  NumberOfTests; scalar_t__ CurrentTestLineNumber; } ;

/* Variables and functions */
 scalar_t__ TEST_PROTECT () ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityConcludeTest () ; 
 int /*<<< orphan*/  setUp () ; 
 int /*<<< orphan*/  tearDown () ; 

void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum)
{
    Unity.CurrentTestName = FuncName;
    Unity.CurrentTestLineNumber = (UNITY_LINE_TYPE)FuncLineNum;
    Unity.NumberOfTests++;

    if (TEST_PROTECT())
    {
        setUp();
        Func();
    }
    if (TEST_PROTECT() && !(Unity.CurrentTestIgnored))
    {
        tearDown();
    }

    UnityConcludeTest();
}