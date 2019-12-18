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
struct TYPE_2__ {unsigned int RepeatCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 
 TYPE_1__ UnityFixture ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int /*<<< orphan*/  UnityPrintNumber (unsigned int) ; 

__attribute__((used)) static void announceTestRun(unsigned int runNumber)
{
    UnityPrint("Unity test run ");
    UnityPrintNumber(runNumber+1);
    UnityPrint(" of ");
    UnityPrintNumber(UnityFixture.RepeatCount);
    UNITY_OUTPUT_CHAR('\n');
}