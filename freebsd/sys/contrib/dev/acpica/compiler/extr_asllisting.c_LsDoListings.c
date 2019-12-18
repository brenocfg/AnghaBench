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
 int /*<<< orphan*/  ASL_FILE_ASM_INCLUDE_OUTPUT ; 
 int /*<<< orphan*/  ASL_FILE_ASM_SOURCE_OUTPUT ; 
 int /*<<< orphan*/  ASL_FILE_C_INCLUDE_OUTPUT ; 
 int /*<<< orphan*/  ASL_FILE_C_OFFSET_OUTPUT ; 
 int /*<<< orphan*/  ASL_FILE_C_SOURCE_OUTPUT ; 
 int /*<<< orphan*/  ASL_FILE_LISTING_OUTPUT ; 
 scalar_t__ AslGbl_AsmIncludeOutputFlag ; 
 scalar_t__ AslGbl_AsmOutputFlag ; 
 scalar_t__ AslGbl_C_IncludeOutputFlag ; 
 scalar_t__ AslGbl_C_OffsetTableFlag ; 
 scalar_t__ AslGbl_C_OutputFlag ; 
 scalar_t__ AslGbl_ListingFlag ; 
 int /*<<< orphan*/  LsGenerateListing (int /*<<< orphan*/ ) ; 

void
LsDoListings (
    void)
{

    if (AslGbl_C_OutputFlag)
    {
        LsGenerateListing (ASL_FILE_C_SOURCE_OUTPUT);
    }

    if (AslGbl_ListingFlag)
    {
        LsGenerateListing (ASL_FILE_LISTING_OUTPUT);
    }

    if (AslGbl_AsmOutputFlag)
    {
        LsGenerateListing (ASL_FILE_ASM_SOURCE_OUTPUT);
    }

    if (AslGbl_C_IncludeOutputFlag)
    {
        LsGenerateListing (ASL_FILE_C_INCLUDE_OUTPUT);
    }

    if (AslGbl_AsmIncludeOutputFlag)
    {
        LsGenerateListing (ASL_FILE_ASM_INCLUDE_OUTPUT);
    }

    if (AslGbl_C_OffsetTableFlag)
    {
        LsGenerateListing (ASL_FILE_C_OFFSET_OUTPUT);
    }
}