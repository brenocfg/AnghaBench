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
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 scalar_t__ AslGbl_CurrentLineBuffer ; 
 scalar_t__ AslGbl_ExpressionTokenBuffer ; 
 scalar_t__ AslGbl_LineBufPtr ; 
 int AslGbl_LineBufferSize ; 
 scalar_t__ AslGbl_MacroTokenBuffer ; 
 scalar_t__ AslGbl_MainTokenBuffer ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  UtReallocLineBuffers (scalar_t__*,int,int) ; 

void
UtExpandLineBuffers (
    void)
{
    UINT32                  NewSize;


    /* Attempt to double the size of all line buffers */

    NewSize = AslGbl_LineBufferSize * 2;
    if (AslGbl_CurrentLineBuffer)
    {
        DbgPrint (ASL_DEBUG_OUTPUT,
            "Increasing line buffer size from %u to %u\n",
            AslGbl_LineBufferSize, NewSize);
    }

    UtReallocLineBuffers (&AslGbl_CurrentLineBuffer, AslGbl_LineBufferSize, NewSize);
    UtReallocLineBuffers (&AslGbl_MainTokenBuffer, AslGbl_LineBufferSize, NewSize);
    UtReallocLineBuffers (&AslGbl_MacroTokenBuffer, AslGbl_LineBufferSize, NewSize);
    UtReallocLineBuffers (&AslGbl_ExpressionTokenBuffer, AslGbl_LineBufferSize, NewSize);

    AslGbl_LineBufPtr = AslGbl_CurrentLineBuffer;
    AslGbl_LineBufferSize = NewSize;
}