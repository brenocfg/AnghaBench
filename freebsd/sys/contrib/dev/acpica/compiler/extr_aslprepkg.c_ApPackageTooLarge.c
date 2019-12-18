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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_MSG_RESERVED_PACKAGE_LENGTH ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 

__attribute__((used)) static void
ApPackageTooLarge (
    const char                  *PredefinedName,
    ACPI_PARSE_OBJECT           *Op,
    UINT32                      Count,
    UINT32                      ExpectedCount)
{

    sprintf (AslGbl_MsgBuffer, "%s: length is %u, only %u required",
        PredefinedName, Count, ExpectedCount);

    AslError (ASL_REMARK, ASL_MSG_RESERVED_PACKAGE_LENGTH, Op, AslGbl_MsgBuffer);
}