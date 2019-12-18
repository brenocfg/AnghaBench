#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_5__ {struct TYPE_5__* Next; TYPE_1__* Files; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Handle; int /*<<< orphan*/  Filename; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ ASL_GLOBAL_FILE_NODE ;

/* Variables and functions */
 TYPE_2__* AslGbl_FilesList ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

FILE *
FlGetFileHandle (
    UINT32                  OutFileId,
    UINT32                  InFileId,
    char                    *Filename)
{
    ASL_GLOBAL_FILE_NODE    *Current = AslGbl_FilesList;


    if (!Filename)
    {
        return (NULL);
    }

    while (Current)
    {
        if (!strcmp (Current->Files[InFileId].Filename, Filename))
        {
            return (Current->Files[OutFileId].Handle);
        }

        Current = Current->Next;
    }

    return (NULL);
}