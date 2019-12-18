#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ CurrentTestIgnored; scalar_t__ CurrentTestFailed; int /*<<< orphan*/  TestFailures; int /*<<< orphan*/  TestIgnores; } ;
struct TYPE_3__ {scalar_t__ Verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 
 TYPE_2__ Unity ; 
 TYPE_1__ UnityFixture ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 

void UnityConcludeFixtureTest(void)
{
    if (Unity.CurrentTestIgnored)
    {
        if (UnityFixture.Verbose)
        {
            UNITY_OUTPUT_CHAR('\n');
        }
        Unity.TestIgnores++;
    }
    else if (!Unity.CurrentTestFailed)
    {
        if (UnityFixture.Verbose)
        {
            UnityPrint(" PASS");
            UNITY_OUTPUT_CHAR('\n');
        }
    }
    else if (Unity.CurrentTestFailed)
    {
        Unity.TestFailures++;
    }

    Unity.CurrentTestFailed = 0;
    Unity.CurrentTestIgnored = 0;
}