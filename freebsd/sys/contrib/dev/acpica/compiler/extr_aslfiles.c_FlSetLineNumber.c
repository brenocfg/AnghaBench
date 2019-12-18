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
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 int /*<<< orphan*/  AslGbl_LogicalLineNumber ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
FlSetLineNumber (
    UINT32                  LineNumber)
{

    DbgPrint (ASL_PARSE_OUTPUT, "\n#line: New line number %u (old %u)\n",
         LineNumber, AslGbl_LogicalLineNumber);

    AslGbl_CurrentLineNumber = LineNumber;
}