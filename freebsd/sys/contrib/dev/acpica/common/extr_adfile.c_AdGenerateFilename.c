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
typedef  size_t UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_SUFFIX_BINARY_TABLE ; 
 char* FilenameBuf ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 

char *
AdGenerateFilename (
    char                    *Prefix,
    char                    *TableId)
{
    UINT32                  i;
    UINT32                  j;


    for (i = 0; Prefix[i]; i++)
    {
        FilenameBuf[i] = Prefix[i];
    }

    FilenameBuf[i] = '_';
    i++;

    for (j = 0; j < 8 && (TableId[j] != ' ') && (TableId[j] != 0); i++, j++)
    {
        FilenameBuf[i] = TableId[j];
    }

    FilenameBuf[i] = 0;
    strcat (FilenameBuf, FILE_SUFFIX_BINARY_TABLE);
    return (FilenameBuf);
}