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
struct TYPE_2__ {char const* TestFile; int /*<<< orphan*/ * XFAILMessage; scalar_t__ TestXPASSES; scalar_t__ TestPasses; scalar_t__ isExpectingFail; scalar_t__ TestXFAILS; scalar_t__ CurrentTestIgnored; scalar_t__ CurrentTestFailed; scalar_t__ TestIgnores; scalar_t__ TestFailures; scalar_t__ NumberOfTests; scalar_t__ CurrentTestLineNumber; int /*<<< orphan*/ * CurrentTestName; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_START () ; 
 TYPE_1__ Unity ; 

void UnityBegin(const char* filename)
{
    Unity.TestFile = filename;
    Unity.CurrentTestName = NULL;
    Unity.CurrentTestLineNumber = 0;
    Unity.NumberOfTests = 0;
    Unity.TestFailures = 0;
    Unity.TestIgnores = 0;
    Unity.CurrentTestFailed = 0;
    Unity.CurrentTestIgnored = 0;
    Unity.TestXFAILS = 0;
    Unity.isExpectingFail = 0;
    Unity.TestPasses = 0;
    Unity.TestXPASSES = 0;
    Unity.XFAILMessage = NULL;

    UNITY_OUTPUT_START();
}