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
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  ASL_ERROR_MSG ;

/* Variables and functions */
 size_t ASL_ERROR ; 
 int /*<<< orphan*/  ASL_FILE_STDERR ; 
 scalar_t__ ASL_MAX_ERROR_COUNT ; 
 int /*<<< orphan*/  AeAddToErrorLog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AePrintException (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AslGbl_DebugFlag ; 
 int /*<<< orphan*/  AslGbl_ErrorLog ; 
 scalar_t__* AslGbl_ExceptionCount ; 
 int /*<<< orphan*/  AslGbl_IgnoreErrors ; 
 int /*<<< orphan*/  AslGbl_NextError ; 
 scalar_t__ AslGbl_SourceLine ; 
 int /*<<< orphan*/  AslInitEnode (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CmCleanupAndExit () ; 
 size_t GetModifiedLevel (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static void
AslLogNewError (
    UINT8                   Level,
    UINT16                  MessageId,
    UINT32                  LineNumber,
    UINT32                  LogicalLineNumber,
    UINT32                  LogicalByteOffset,
    UINT32                  Column,
    char                    *Filename,
    char                    *Message,
    char                    *SourceLine,
    ASL_ERROR_MSG           *SubError)
{
    ASL_ERROR_MSG           *Enode = NULL;
    UINT8                   ModifiedLevel = GetModifiedLevel (Level, MessageId);


    AslInitEnode (&Enode, ModifiedLevel, MessageId, LineNumber,
        LogicalLineNumber, LogicalByteOffset, Column, Filename, Message,
        SourceLine, SubError);

    /* Add the new node to the error node list */

    AeAddToErrorLog (Enode);

    if (AslGbl_DebugFlag)
    {
        /* stderr is a file, send error to it immediately */

        AePrintException (ASL_FILE_STDERR, Enode, NULL);
    }

    AslGbl_ExceptionCount[ModifiedLevel]++;
    if (!AslGbl_IgnoreErrors && AslGbl_ExceptionCount[ASL_ERROR] > ASL_MAX_ERROR_COUNT)
    {
        printf ("\nMaximum error count (%u) exceeded\n", ASL_MAX_ERROR_COUNT);

        AslGbl_SourceLine = 0;
        AslGbl_NextError = AslGbl_ErrorLog;
        CmCleanupAndExit ();
        exit(1);
    }

    return;
}