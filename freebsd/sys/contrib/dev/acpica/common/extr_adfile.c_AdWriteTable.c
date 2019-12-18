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
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,char*) ; 
 char* AdGenerateFilename (char*,char*) ; 
 int /*<<< orphan*/  AdWriteBuffer (char*,char*,int /*<<< orphan*/ ) ; 

void
AdWriteTable (
    ACPI_TABLE_HEADER       *Table,
    UINT32                  Length,
    char                    *TableName,
    char                    *OemTableId)
{
    char                    *Filename;


    Filename = AdGenerateFilename (TableName, OemTableId);
    AdWriteBuffer (Filename, (char *) Table, Length);

    AcpiOsPrintf ("Table [%s] written to \"%s\"\n", TableName, Filename);
}