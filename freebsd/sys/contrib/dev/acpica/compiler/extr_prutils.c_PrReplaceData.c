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
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void
PrReplaceData (
    char                    *Buffer,
    UINT32                  LengthToRemove,
    char                    *BufferToAdd,
    UINT32                  LengthToAdd)
{
    UINT32                  BufferLength;


    /* Buffer is a string, so the length must include the terminating zero */

    BufferLength = strlen (Buffer) + 1;

    if (LengthToRemove != LengthToAdd)
    {
        /*
         * Move some of the existing data
         * 1) If adding more bytes than removing, make room for the new data
         * 2) if removing more bytes than adding, delete the extra space
         */
        if (LengthToRemove > 0)
        {
            memmove ((Buffer + LengthToAdd), (Buffer + LengthToRemove),
                (BufferLength - LengthToRemove));
        }
    }

    /* Now we can move in the new data */

    if (LengthToAdd > 0)
    {
        memmove (Buffer, BufferToAdd, LengthToAdd);
    }
}