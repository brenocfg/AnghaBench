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
typedef  int /*<<< orphan*/  _U_SINT ;
struct TYPE_2__ {unsigned int TestFailures; unsigned int TestXPASSES; scalar_t__ TestIgnores; scalar_t__ TestXFAILS; scalar_t__ TestPasses; scalar_t__ NumberOfTests; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_COMPLETE () ; 
 int /*<<< orphan*/  UNITY_PRINT_EOL ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnityPrintFail () ; 
 int /*<<< orphan*/  UnityPrintNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnityPrintOk () ; 
 int /*<<< orphan*/  UnityStrBreaker ; 
 int /*<<< orphan*/  UnityStrResultsFailures ; 
 int /*<<< orphan*/  UnityStrResultsIgnored ; 
 int /*<<< orphan*/  UnityStrResultsPass ; 
 int /*<<< orphan*/  UnityStrResultsTests ; 
 int /*<<< orphan*/  UnityStrResultsXFAIL ; 
 int /*<<< orphan*/  UnityStrResultsXPASS ; 

int UnityEnd(void)
{
    UNITY_PRINT_EOL;
    UnityPrint(UnityStrBreaker);
    UNITY_PRINT_EOL;
    UnityPrintNumber((_U_SINT)(Unity.NumberOfTests));
    UnityPrint(UnityStrResultsTests);
    UNITY_PRINT_EOL;
    UnityPrintNumber((_U_SINT)(Unity.TestPasses));
    UnityPrint(UnityStrResultsPass);
    UNITY_PRINT_EOL;
    UnityPrintNumber((_U_SINT)(Unity.TestXFAILS));
    UnityPrint(UnityStrResultsXFAIL);
    UNITY_PRINT_EOL;
    UnityPrintNumber((_U_SINT)(Unity.TestFailures));
    UnityPrint(UnityStrResultsFailures);
    UNITY_PRINT_EOL;
    UnityPrintNumber((_U_SINT)(Unity.TestXPASSES));
    UnityPrint(UnityStrResultsXPASS);
    UNITY_PRINT_EOL;
    UnityPrintNumber((_U_SINT)(Unity.TestIgnores));
    UnityPrint(UnityStrResultsIgnored);
    UNITY_PRINT_EOL;

    UNITY_PRINT_EOL;
    if (Unity.TestFailures == 0U && Unity.TestXPASSES == 0U)
    {
        UnityPrintOk();
    }
    else
    {
        UnityPrintFail();
    }
    UNITY_PRINT_EOL;
    UNITY_OUTPUT_COMPLETE();
    return (int)(Unity.TestFailures);
}