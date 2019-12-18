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
 scalar_t__ AE_ERROR ; 
 int /*<<< orphan*/  ASL_FILE_INPUT ; 
 int /*<<< orphan*/  AslInsertLineBuffer (int) ; 
 int /*<<< orphan*/  AslResetCurrentLineBuffer () ; 
 scalar_t__ FlReadFile (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
CmFlushSourceCode (
    void)
{
    char                    Buffer;


    while (FlReadFile (ASL_FILE_INPUT, &Buffer, 1) != AE_ERROR)
    {
        AslInsertLineBuffer ((int) Buffer);
    }

    AslResetCurrentLineBuffer ();
}