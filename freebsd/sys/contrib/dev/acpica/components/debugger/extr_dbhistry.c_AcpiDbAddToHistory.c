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
typedef  scalar_t__ UINT16 ;
struct TYPE_2__ {char* Command; int /*<<< orphan*/  CmdNum; } ;

/* Variables and functions */
 TYPE_1__* AcpiGbl_HistoryBuffer ; 
 size_t AcpiGbl_LoHistory ; 
 int /*<<< orphan*/  AcpiGbl_NextCmdNum ; 
 size_t AcpiGbl_NextHistoryIndex ; 
 size_t AcpiGbl_NumHistory ; 
 void* AcpiOsAllocate (scalar_t__) ; 
 int /*<<< orphan*/  AcpiOsFree (char*) ; 
 size_t HISTORY_SIZE ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
AcpiDbAddToHistory (
    char                    *CommandLine)
{
    UINT16                  CmdLen;
    UINT16                  BufferLen;

    /* Put command into the next available slot */

    CmdLen = (UINT16) strlen (CommandLine);
    if (!CmdLen)
    {
        return;
    }

    if (AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].Command != NULL)
    {
        BufferLen = (UINT16) strlen (
            AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].Command);

        if (CmdLen > BufferLen)
        {
            AcpiOsFree (AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].
                Command);
            AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].Command =
                AcpiOsAllocate (CmdLen + 1);
        }
    }
    else
    {
        AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].Command =
            AcpiOsAllocate (CmdLen + 1);
    }

    strcpy (AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].Command,
        CommandLine);

    AcpiGbl_HistoryBuffer[AcpiGbl_NextHistoryIndex].CmdNum =
        AcpiGbl_NextCmdNum;

    /* Adjust indexes */

    if ((AcpiGbl_NumHistory == HISTORY_SIZE) &&
        (AcpiGbl_NextHistoryIndex == AcpiGbl_LoHistory))
    {
        AcpiGbl_LoHistory++;
        if (AcpiGbl_LoHistory >= HISTORY_SIZE)
        {
            AcpiGbl_LoHistory = 0;
        }
    }

    AcpiGbl_NextHistoryIndex++;
    if (AcpiGbl_NextHistoryIndex >= HISTORY_SIZE)
    {
        AcpiGbl_NextHistoryIndex = 0;
    }

    AcpiGbl_NextCmdNum++;
    if (AcpiGbl_NumHistory < HISTORY_SIZE)
    {
        AcpiGbl_NumHistory++;
    }
}