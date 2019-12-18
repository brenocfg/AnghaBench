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
typedef  scalar_t__ UINT32 ;
typedef  size_t UINT16 ;
struct TYPE_2__ {scalar_t__ CmdNum; char* Command; } ;

/* Variables and functions */
 TYPE_1__* AcpiGbl_HistoryBuffer ; 
 size_t AcpiGbl_LoHistory ; 
 scalar_t__ AcpiGbl_NumHistory ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,size_t) ; 
 size_t HISTORY_SIZE ; 

char *
AcpiDbGetHistoryByIndex (
    UINT32                  CmdNum)
{
    UINT32                  i;
    UINT16                  HistoryIndex;


    /* Search history buffer */

    HistoryIndex = AcpiGbl_LoHistory;
    for (i = 0; i < AcpiGbl_NumHistory; i++)
    {
        if (AcpiGbl_HistoryBuffer[HistoryIndex].CmdNum == CmdNum)
        {
            /* Found the command, return it */

            return (AcpiGbl_HistoryBuffer[HistoryIndex].Command);
        }

        /* History buffer is circular */

        HistoryIndex++;
        if (HistoryIndex >= HISTORY_SIZE)
        {
            HistoryIndex = 0;
        }
    }

    AcpiOsPrintf ("Invalid history number: %u\n", HistoryIndex);
    return (NULL);
}