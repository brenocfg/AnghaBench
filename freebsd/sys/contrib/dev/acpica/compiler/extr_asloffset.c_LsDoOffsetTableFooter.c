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
 scalar_t__ AslGbl_CurrentAmlOffset ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*) ; 

void
LsDoOffsetTableFooter (
    UINT32                  FileId)
{

    FlPrintFile (FileId,
        "    {NULL,0,0,0,0,0} /* Table terminator */\n};\n\n");
    AslGbl_CurrentAmlOffset = 0;
}