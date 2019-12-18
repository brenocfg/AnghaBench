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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {struct TYPE_5__* Next; TYPE_1__* Files; } ;
struct TYPE_4__ {int /*<<< orphan*/  Filename; } ;
typedef  TYPE_2__ ASL_GLOBAL_FILE_NODE ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
 TYPE_2__* AslGbl_FilesList ; 
 int /*<<< orphan*/  FALSE ; 
#define  FILE_NOT_FOUND 130 
 int FlSwitchFileSet (int /*<<< orphan*/ ) ; 
#define  SWITCH_TO_DIFFERENT_FILE 129 
#define  SWITCH_TO_SAME_FILE 128 
 int /*<<< orphan*/  UtDisplayErrorSummary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtDisplayOneSummary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
UtDisplaySummary (
    UINT32                  FileId)
{
    ASL_GLOBAL_FILE_NODE    *Current = AslGbl_FilesList;


    while (Current)
    {
        switch  (FlSwitchFileSet(Current->Files[ASL_FILE_INPUT].Filename))
        {
            case SWITCH_TO_SAME_FILE:
            case SWITCH_TO_DIFFERENT_FILE:

                UtDisplayOneSummary (FileId, FALSE);
                Current = Current->Next;
                break;

            case FILE_NOT_FOUND:
            default:

                Current = NULL;
                break;
        }
    }
    UtDisplayErrorSummary (FileId);
}