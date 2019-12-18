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
struct TYPE_2__ {int isExpectingFail; int CurrentTestFailed; char* XFAILMessage; scalar_t__ CurrentTestIgnored; int /*<<< orphan*/  TestFailures; int /*<<< orphan*/  TestXPASSES; int /*<<< orphan*/  CurrentTestLineNumber; int /*<<< orphan*/  TestFile; int /*<<< orphan*/  TestPasses; int /*<<< orphan*/  TestIgnores; int /*<<< orphan*/  TestXFAILS; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_PRINT_EOL ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnityStrPass ; 
 int /*<<< orphan*/  UnityStrXPASS ; 
 int /*<<< orphan*/  UnityTestResultsBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void UnityConcludeTest(void)
{
#if 0
	if (Unity.isExpectingFail == 1 && Unity.CurrentTestFailed == 0)
	{
		printf("FAIL WAS EXPECTED, BUT IT DIDN'T HAPPEN?!");
		Unity.TestXPASSES++;
	}

	else
#endif
	//cant be ignored and accepting fail at the same time!
	if (Unity.isExpectingFail == 1 && Unity.CurrentTestFailed == 1)
	{
		Unity.TestXFAILS++; //error message?!
		if (Unity.XFAILMessage != NULL)
		{
			if (Unity.XFAILMessage[0] != ' ')
			{
				printf(" ");
			}

			printf("| ");
			printf("%s", Unity.XFAILMessage);
			Unity.XFAILMessage = NULL;
		}
		else
		{
			printf(" - EXPECTED FAIL!");
		}
	}
	else

    if (Unity.CurrentTestIgnored)
    {
        Unity.TestIgnores++;
    }
    else if (!Unity.CurrentTestFailed)
    {
	if(Unity.isExpectingFail == 0) {
		UnityTestResultsBegin(Unity.TestFile, Unity.CurrentTestLineNumber);
		UnityPrint(UnityStrPass);
		Unity.TestPasses++;
	}

	//probably should remove the if... part
	else if (Unity.isExpectingFail == 1 && Unity.CurrentTestFailed == 0)
	{

		UnityTestResultsBegin(Unity.TestFile, Unity.CurrentTestLineNumber);
		UnityPrint(UnityStrXPASS);
		Unity.TestXPASSES++;

		printf(" - FAIL WAS EXPECTED, BUT DIDN'T HAPPEN?!");
		//if (Unity.TestPasses > 0) { Unity.TestPasses--; }
	}
    }
    else
    {
        Unity.TestFailures++;
    }

    Unity.CurrentTestFailed = 0;
    Unity.CurrentTestIgnored = 0;
    Unity.isExpectingFail = 0;

    UNITY_PRINT_EOL;
}