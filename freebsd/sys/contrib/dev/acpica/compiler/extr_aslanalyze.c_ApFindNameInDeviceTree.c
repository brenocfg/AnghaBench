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
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ AE_CTRL_TRUE ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_DOWNWARD ; 
 int /*<<< orphan*/  ApDeviceSubtreeWalk ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TrWalkParseTree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

BOOLEAN
ApFindNameInDeviceTree (
    char                    *Name,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;


    Status = TrWalkParseTree (Op, ASL_WALK_VISIT_DOWNWARD,
        ApDeviceSubtreeWalk, NULL, Name);

    if (Status == AE_CTRL_TRUE)
    {
        return (TRUE);  /* Found a match */
    }

    return (FALSE);
}