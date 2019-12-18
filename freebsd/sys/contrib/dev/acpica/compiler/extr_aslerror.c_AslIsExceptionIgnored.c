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
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ AslGbl_AllExceptionsDisabled ; 
 int AslIsExceptionDisabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AslIsExceptionExpected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN
AslIsExceptionIgnored (
    UINT8                   Level,
    UINT16                  MessageId)
{
    BOOLEAN                 ExceptionIgnored;


    /* Note: this allows exception to be disabled and expected */

    ExceptionIgnored = AslIsExceptionDisabled (Level, MessageId);
    ExceptionIgnored |= AslIsExceptionExpected (Level, MessageId);

    return (AslGbl_AllExceptionsDisabled || ExceptionIgnored);
}