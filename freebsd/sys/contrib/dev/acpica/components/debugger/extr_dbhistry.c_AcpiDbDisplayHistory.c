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
struct TYPE_2__ {scalar_t__ Command; int /*<<< orphan*/  CmdNum; } ;

/* Variables and functions */
 TYPE_1__* AcpiGbl_HistoryBuffer ; 
 size_t AcpiGbl_LoHistory ; 
 scalar_t__ AcpiGbl_NumHistory ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t HISTORY_SIZE ; 

void
AcpiDbDisplayHistory (
    void)
{
    UINT32                  i;
    UINT16                  HistoryIndex;


    HistoryIndex = AcpiGbl_LoHistory;

    /* Dump entire history buffer */

    for (i = 0; i < AcpiGbl_NumHistory; i++)
    {
        if (AcpiGbl_HistoryBuffer[HistoryIndex].Command)
        {
            AcpiOsPrintf ("%3u  %s\n",
                AcpiGbl_HistoryBuffer[HistoryIndex].CmdNum,
                AcpiGbl_HistoryBuffer[HistoryIndex].Command);
        }

        HistoryIndex++;
        if (HistoryIndex >= HISTORY_SIZE)
        {
            HistoryIndex = 0;
        }
    }
}