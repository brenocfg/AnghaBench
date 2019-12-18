#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ TotalUnreferencedObjects; scalar_t__ TotalObjects; scalar_t__ TotalUnreferenceUserMethods; scalar_t__ TotalUserMethods; scalar_t__ TotalPredefinedMethods; } ;
typedef  TYPE_1__ ASL_XREF_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_FILE_XREF_OUTPUT ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_DOWNWARD ; 
 int /*<<< orphan*/  AslGbl_CrossReferenceOutput ; 
 int /*<<< orphan*/  AslGbl_ParseTreeRoot ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OtPrintHeaders (char*) ; 
 int /*<<< orphan*/  OtXrefWalkPart2 ; 
 int /*<<< orphan*/  OtXrefWalkPart3 ; 
 int /*<<< orphan*/  TrWalkParseTree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
OtCreateXrefFile (
    void)
{
    ASL_XREF_INFO           XrefInfo;


    /* Build cross-reference output file if requested */

    if (!AslGbl_CrossReferenceOutput)
    {
        return;
    }

    memset (&XrefInfo, 0, sizeof (ASL_XREF_INFO));

    /* Cross-reference output file, part 2 (Method invocations) */

    OtPrintHeaders ("Part 2: Method Reference Map "
        "(Invocations of each user-defined control method)");

    TrWalkParseTree (AslGbl_ParseTreeRoot, ASL_WALK_VISIT_DOWNWARD,
        OtXrefWalkPart2, NULL, &XrefInfo);

    /* Cross-reference output file, part 3 (All other object refs) */

    OtPrintHeaders ("Part 3: Full Object Reference Map "
        "(Methods that reference each object in namespace");

    TrWalkParseTree (AslGbl_ParseTreeRoot, ASL_WALK_VISIT_DOWNWARD,
        OtXrefWalkPart3, NULL, &XrefInfo);

    /* Cross-reference summary */

    FlPrintFile (ASL_FILE_XREF_OUTPUT, "\n\nObject Summary\n");

    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "\nTotal methods:                   %u\n",
        XrefInfo.TotalPredefinedMethods + XrefInfo.TotalUserMethods);
    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "Total predefined methods:        %u\n",
        XrefInfo.TotalPredefinedMethods);

    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "\nTotal user methods:              %u\n",
        XrefInfo.TotalUserMethods);
    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "Total unreferenced user methods  %u\n",
        XrefInfo.TotalUnreferenceUserMethods);

    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "\nTotal defined objects:           %u\n",
        XrefInfo.TotalObjects);
    FlPrintFile (ASL_FILE_XREF_OUTPUT,
        "Total unreferenced objects:      %u\n",
        XrefInfo.TotalUnreferencedObjects);
}