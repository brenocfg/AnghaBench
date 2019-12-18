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
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 size_t ACPI_ARRAY_LENGTH (char**) ; 
 scalar_t__ ASL_MSG_MAIN_COMPILER_END ; 
 scalar_t__ ASL_MSG_PREPROCESSOR ; 
 scalar_t__ ASL_MSG_PREPROCESSOR_END ; 
 scalar_t__ ASL_MSG_TABLE_COMPILER ; 
 scalar_t__ ASL_MSG_TABLE_COMPILER_END ; 
 char** AslCompilerMsgs ; 
 char** AslPreprocessorMsgs ; 
 char** AslTableCompilerMsgs ; 

const char *
AeDecodeMessageId (
    UINT16                  MessageId)
{
    UINT32                  Index;
    const char              **MessageTable;


    /* Main ASL Compiler messages */

    if (MessageId <= ASL_MSG_MAIN_COMPILER_END)
    {
        MessageTable = AslCompilerMsgs;
        Index = MessageId;

        if (Index >= ACPI_ARRAY_LENGTH (AslCompilerMsgs))
        {
            return ("[Unknown ASL Compiler exception ID]");
        }
    }

    /* Data Table Compiler messages */

    else if (MessageId <= ASL_MSG_TABLE_COMPILER_END)
    {
        MessageTable = AslTableCompilerMsgs;
        Index = MessageId - ASL_MSG_TABLE_COMPILER;

        if (Index >= ACPI_ARRAY_LENGTH (AslTableCompilerMsgs))
        {
            return ("[Unknown Table Compiler exception ID]");
        }
    }

    /* Preprocessor messages */

    else if (MessageId <= ASL_MSG_PREPROCESSOR_END)
    {
        MessageTable = AslPreprocessorMsgs;
        Index = MessageId - ASL_MSG_PREPROCESSOR;

        if (Index >= ACPI_ARRAY_LENGTH (AslPreprocessorMsgs))
        {
            return ("[Unknown Preprocessor exception ID]");
        }
    }

    /* Everything else is unknown */

    else
    {
        return ("[Unknown exception/component ID]");
    }

    return (MessageTable[Index]);
}