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
struct TYPE_5__ {struct TYPE_5__* Next; TYPE_1__* Files; } ;
struct TYPE_4__ {int /*<<< orphan*/  Filename; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ASL_GLOBAL_FILE_NODE ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
 TYPE_2__* AslGbl_FilesList ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
FlInputFileExists (
    char                    *Filename)
{
    ASL_GLOBAL_FILE_NODE    *Current = AslGbl_FilesList;


    while (Current)
    {
        if (!strcmp (Filename, Current->Files[ASL_FILE_INPUT].Filename))
        {
            return (TRUE);
        }

        Current = Current->Next;
    }

    return (FALSE);
}