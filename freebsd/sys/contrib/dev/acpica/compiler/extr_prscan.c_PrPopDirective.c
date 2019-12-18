#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Name; } ;
struct TYPE_4__ {size_t Directive; int /*<<< orphan*/  Argument; struct TYPE_4__* Next; scalar_t__ IgnoringThisCodeBlock; } ;
typedef  TYPE_1__ DIRECTIVE_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 TYPE_3__* AslGbl_DirectiveInfo ; 
 TYPE_1__* AslGbl_DirectiveStack ; 
 int AslGbl_IfDepth ; 
 scalar_t__ AslGbl_IgnoringThisCodeBlock ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ACPI_STATUS
PrPopDirective (
    void)
{
    DIRECTIVE_INFO          *Info;


    /* Check for empty stack */

    Info = AslGbl_DirectiveStack;
    if (!Info)
    {
        return (AE_ERROR);
    }

    /* Pop one item, keep globals up-to-date */

    AslGbl_IfDepth--;
    AslGbl_IgnoringThisCodeBlock = Info->IgnoringThisCodeBlock;
    AslGbl_DirectiveStack = Info->Next;

    DbgPrint (ASL_DEBUG_OUTPUT,
        "Pr(%.4u) - [%u %s] %*s Popped [#%s %s]: IgnoreFlag now = %s\n",
        AslGbl_CurrentLineNumber, AslGbl_IfDepth,
        AslGbl_IgnoringThisCodeBlock ? "I" : "E",
        AslGbl_IfDepth * 4, " ",
        AslGbl_DirectiveInfo[Info->Directive].Name,
        Info->Argument, AslGbl_IgnoringThisCodeBlock ? "TRUE" : "FALSE");

    return (AE_OK);
}