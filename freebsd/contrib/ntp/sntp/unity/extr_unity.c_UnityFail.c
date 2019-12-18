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
struct TYPE_2__ {int /*<<< orphan*/  TestFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_FAIL_AND_BAIL ; 
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 
 int /*<<< orphan*/  UNITY_SKIP_EXECUTION ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityPrint (char const*) ; 
 int /*<<< orphan*/  UnityPrintFail () ; 
 int /*<<< orphan*/  UnityTestResultsBegin (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

void UnityFail(const char* msg, const UNITY_LINE_TYPE line)
{
    UNITY_SKIP_EXECUTION;

    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrintFail();
    if (msg != NULL)
    {
      UNITY_OUTPUT_CHAR(':');
      if (msg[0] != ' ')
      {
        UNITY_OUTPUT_CHAR(' ');
      }
      UnityPrint(msg);
    }
    UNITY_FAIL_AND_BAIL;
}