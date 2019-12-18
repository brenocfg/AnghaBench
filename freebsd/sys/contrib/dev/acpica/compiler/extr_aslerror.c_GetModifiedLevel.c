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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 size_t AeBuildFullExceptionCode (int /*<<< orphan*/ ,size_t) ; 
 size_t* AslGbl_ElevatedMessages ; 
 size_t AslGbl_ElevatedMessagesIndex ; 

__attribute__((used)) static UINT8
GetModifiedLevel (
    UINT8                   Level,
    UINT16                  MessageId)
{
    UINT16                  i;
    UINT16                  ExceptionCode;


    ExceptionCode = AeBuildFullExceptionCode (Level, MessageId);

    for (i = 0; i < AslGbl_ElevatedMessagesIndex; i++)
    {
        if (ExceptionCode == AslGbl_ElevatedMessages[i])
        {
            return (ASL_ERROR);
        }
    }

    return (Level);
}