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
typedef  int UINT8 ;
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
#define  ASL_ERROR 132 
#define  ASL_REMARK 131 
#define  ASL_WARNING 130 
#define  ASL_WARNING2 129 
#define  ASL_WARNING3 128 
 size_t AeBuildFullExceptionCode (int,int /*<<< orphan*/ ) ; 
 size_t* AslGbl_DisabledMessages ; 
 size_t AslGbl_DisabledMessagesIndex ; 
 int AslGbl_WarningLevel ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AslIsExceptionDisabled (
    UINT8                   Level,
    UINT16                  MessageId)
{
    UINT32                  EncodedMessageId;
    UINT32                  i;


    switch (Level)
    {
    case ASL_WARNING2:
    case ASL_WARNING3:

        /* Check for global disable via -w1/-w2/-w3 options */

        if (Level > AslGbl_WarningLevel)
        {
            return (TRUE);
        }
        /* Fall through */

    case ASL_WARNING:
    case ASL_REMARK:
    case ASL_ERROR:
        /*
         * Ignore this error/warning/remark if it has been disabled by
         * the user (-vw option)
         */
        EncodedMessageId = AeBuildFullExceptionCode (Level, MessageId);
        for (i = 0; i < AslGbl_DisabledMessagesIndex; i++)
        {
            /* Simple implementation via fixed array */

            if (EncodedMessageId == AslGbl_DisabledMessages[i])
            {
                return (TRUE);
            }
        }
        break;

    default:
        break;
    }

    return (FALSE);
}