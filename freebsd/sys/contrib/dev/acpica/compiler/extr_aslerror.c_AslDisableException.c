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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int ASL_MAX_DISABLED_MESSAGES ; 
 int* AslGbl_DisabledMessages ; 
 int AslGbl_DisabledMessagesIndex ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ACPI_STATUS
AslDisableException (
    char                    *MessageIdString)
{
    UINT32                  MessageId;


    /* Convert argument to an integer and validate it */

    MessageId = (UINT32) strtoul (MessageIdString, NULL, 0);

    if ((MessageId < 2000) || (MessageId > 6999))
    {
        printf ("\"%s\" is not a valid warning/remark/error ID\n",
            MessageIdString);
        return (AE_BAD_PARAMETER);
    }

    /* Insert value into the global disabled message array */

    if (AslGbl_DisabledMessagesIndex >= ASL_MAX_DISABLED_MESSAGES)
    {
        printf ("Too many messages have been disabled (max %d)\n",
            ASL_MAX_DISABLED_MESSAGES);
        return (AE_LIMIT);
    }

    AslGbl_DisabledMessages[AslGbl_DisabledMessagesIndex] = MessageId;
    AslGbl_DisabledMessagesIndex++;
    return (AE_OK);
}