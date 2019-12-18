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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {size_t MessageId; int /*<<< orphan*/  MessageReceived; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 size_t AeBuildFullExceptionCode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AslGbl_ExpectedMessages ; 
 size_t AslGbl_ExpectedMessagesIndex ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AslIsExceptionExpected (
    UINT8                   Level,
    UINT16                  MessageId)
{
    UINT32                  EncodedMessageId;
    UINT32                  i;


    /* Mark this exception as received */

    EncodedMessageId = AeBuildFullExceptionCode (Level, MessageId);
    for (i = 0; i < AslGbl_ExpectedMessagesIndex; i++)
    {
        /* Simple implementation via fixed array */

        if (EncodedMessageId == AslGbl_ExpectedMessages[i].MessageId)
        {
            return (AslGbl_ExpectedMessages[i].MessageReceived = TRUE);
        }
    }

    return (FALSE);
}