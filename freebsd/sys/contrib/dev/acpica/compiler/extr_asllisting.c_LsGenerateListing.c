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
typedef  scalar_t__ UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  Filename; } ;

/* Variables and functions */
 scalar_t__ ACPI_TO_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 scalar_t__ ASL_FILE_C_OFFSET_OUTPUT ; 
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_FILE_SOURCE_OUTPUT ; 
 scalar_t__ ASL_WALK_VISIT_DB_SEPARATELY ; 
 scalar_t__ ASL_WALK_VISIT_DOWNWARD ; 
 scalar_t__ AslGbl_CurrentAmlOffset ; 
 int /*<<< orphan*/  AslGbl_CurrentDB ; 
 scalar_t__ AslGbl_CurrentHexColumn ; 
 TYPE_1__* AslGbl_Files ; 
 scalar_t__ AslGbl_SourceLine ; 
 int /*<<< orphan*/  FlSeekFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsAmlListingWalk ; 
 int /*<<< orphan*/  LsAmlOffsetWalk ; 
 int /*<<< orphan*/  LsDoOffsetTableFooter (scalar_t__) ; 
 int /*<<< orphan*/  LsDoOffsetTableHeader (scalar_t__) ; 
 int /*<<< orphan*/  LsFinishSourceListing (scalar_t__) ; 
 int /*<<< orphan*/  LsPushNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TrWalkParseTree (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
LsGenerateListing (
    UINT32                  FileId)
{
    UINT32                  WalkMode = ASL_WALK_VISIT_DOWNWARD | ASL_WALK_VISIT_DB_SEPARATELY;

    /* Start at the beginning of both the source and AML files */

    FlSeekFile (ASL_FILE_SOURCE_OUTPUT, 0);
    FlSeekFile (ASL_FILE_AML_OUTPUT, 0);
    AslGbl_SourceLine = 0;
    AslGbl_CurrentHexColumn = 0;
    LsPushNode (AslGbl_Files[ASL_FILE_INPUT].Filename);

    if (FileId == ASL_FILE_C_OFFSET_OUTPUT)
    {
        AslGbl_CurrentAmlOffset = 0;

        /* Offset table file has a special header and footer */

        LsDoOffsetTableHeader (FileId);

        TrWalkParseTree (AslGbl_CurrentDB, WalkMode,
            LsAmlOffsetWalk, NULL, (void *) ACPI_TO_POINTER (FileId));
        LsDoOffsetTableFooter (FileId);
        return;
    }

    /* Process all parse nodes */

    TrWalkParseTree (AslGbl_CurrentDB, WalkMode,
        LsAmlListingWalk, NULL, (void *) ACPI_TO_POINTER (FileId));

    /* Final processing */

    LsFinishSourceListing (FileId);
}