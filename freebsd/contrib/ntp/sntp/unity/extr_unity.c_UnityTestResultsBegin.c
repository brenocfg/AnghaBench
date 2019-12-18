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
typedef  scalar_t__ UNITY_LINE_TYPE ;
struct TYPE_2__ {char const* CurrentTestName; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityPrint (char const*) ; 
 int /*<<< orphan*/  UnityPrintNumber (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UnityTestResultsBegin(const char* file, const UNITY_LINE_TYPE line)
{
    UnityPrint(file);
    UNITY_OUTPUT_CHAR(':');
    UnityPrintNumber((_U_SINT)line);
    UNITY_OUTPUT_CHAR(':');
    UnityPrint(Unity.CurrentTestName);
    UNITY_OUTPUT_CHAR(':');
}