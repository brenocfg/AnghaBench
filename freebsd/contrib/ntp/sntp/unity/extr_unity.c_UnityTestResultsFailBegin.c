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
typedef  int /*<<< orphan*/  UNITY_LINE_TYPE ;
struct TYPE_2__ {scalar_t__ isExpectingFail; int /*<<< orphan*/  TestFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityPrint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnityStrFail ; 
 int /*<<< orphan*/  UnityStrXFAIL ; 
 int /*<<< orphan*/  UnityTestResultsBegin (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void UnityTestResultsFailBegin(const UNITY_LINE_TYPE line)
{
    UnityTestResultsBegin(Unity.TestFile, line);
	if (Unity.isExpectingFail)
	{
		UnityPrint(UnityStrXFAIL);
	}
	else
	{
		UnityPrint(UnityStrFail);
	}

    UNITY_OUTPUT_CHAR(':');
}