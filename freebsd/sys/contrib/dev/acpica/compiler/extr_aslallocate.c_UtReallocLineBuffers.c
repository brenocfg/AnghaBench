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
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_ALLOCATION ; 
 int /*<<< orphan*/  AslAbort () ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 char* realloc (char*,int) ; 

void
UtReallocLineBuffers (
    char                    **Buffer,
    UINT32                  OldSize,
    UINT32                  NewSize)
{

    *Buffer = realloc (*Buffer, NewSize);
    if (*Buffer)
    {
        memset (*Buffer + OldSize, 0, NewSize - OldSize);
        return;
    }

    printf ("Could not increase line buffer size from %u to %u\n",
        OldSize, NewSize);

    AslError (ASL_ERROR, ASL_MSG_BUFFER_ALLOCATION, NULL, NULL);
    AslAbort ();
}