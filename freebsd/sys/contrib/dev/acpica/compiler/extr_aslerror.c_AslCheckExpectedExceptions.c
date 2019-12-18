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
typedef  size_t UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  MessageIdStr; int /*<<< orphan*/  MessageReceived; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_EXCEPTION_NOT_RECEIVED ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* AslGbl_ExpectedMessages ; 
 size_t AslGbl_ExpectedMessagesIndex ; 

void
AslCheckExpectedExceptions (
    void)
{
    UINT8                   i;


    for (i = 0; i < AslGbl_ExpectedMessagesIndex; ++i)
    {
        if (!AslGbl_ExpectedMessages[i].MessageReceived)
        {
            AslError (ASL_ERROR, ASL_MSG_EXCEPTION_NOT_RECEIVED, NULL,
                AslGbl_ExpectedMessages[i].MessageIdStr);
        }
    }
}