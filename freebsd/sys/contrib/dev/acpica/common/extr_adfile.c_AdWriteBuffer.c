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
typedef  int INT32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ ACPI_SIZE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static INT32
AdWriteBuffer (
    char                    *Filename,
    char                    *Buffer,
    UINT32                  Length)
{
    FILE                    *File;
    ACPI_SIZE               Actual;


    File = fopen (Filename, "wb");
    if (!File)
    {
        printf ("Could not open file %s\n", Filename);
        return (-1);
    }

    Actual = fwrite (Buffer, 1, (size_t) Length, File);
    if (Actual != Length)
    {
        printf ("Could not write to file %s\n", Filename);
    }

    fclose (File);
    return ((INT32) Actual);
}