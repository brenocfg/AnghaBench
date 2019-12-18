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
struct TYPE_2__ {char* Filename; } ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,char*,char*) ; 

void
FlSetFilename (
    char                    *Filename)
{

    DbgPrint (ASL_PARSE_OUTPUT, "\n#line: New filename %s (old %s)\n",
         Filename, AslGbl_Files[ASL_FILE_INPUT].Filename);

    /* No need to free any existing filename */

    AslGbl_Files[ASL_FILE_INPUT].Filename = Filename;
}