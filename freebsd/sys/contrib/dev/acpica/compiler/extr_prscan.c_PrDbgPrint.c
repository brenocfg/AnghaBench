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

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 int AslGbl_IfDepth ; 
 scalar_t__ AslGbl_IgnoringThisCodeBlock ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int,char*,char*,char*,int) ; 

__attribute__((used)) static void
PrDbgPrint (
    char                    *Action,
    char                    *DirectiveName)
{

    DbgPrint (ASL_DEBUG_OUTPUT, "Pr(%.4u) - [%u %s] "
        "%*s %s #%s, IfDepth %u\n",
        AslGbl_CurrentLineNumber, AslGbl_IfDepth,
        AslGbl_IgnoringThisCodeBlock ? "I" : "E",
        AslGbl_IfDepth * 4, " ",
        Action, DirectiveName, AslGbl_IfDepth);
}