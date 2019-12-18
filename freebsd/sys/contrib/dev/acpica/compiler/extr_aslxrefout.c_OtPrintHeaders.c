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
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_FILE_XREF_OUTPUT ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strlen (char*) ; 

void
OtPrintHeaders (
    char                    *Message)
{
    UINT32                  Length;


    Length = strlen (Message);

    FlPrintFile (ASL_FILE_XREF_OUTPUT, "\n\n%s\n", Message);
    while (Length)
    {
        FlPrintFile (ASL_FILE_XREF_OUTPUT, "-");
        Length--;
    }

    FlPrintFile (ASL_FILE_XREF_OUTPUT, "\n\nLineno   %-40s Description\n",
        "Full Pathname");
}